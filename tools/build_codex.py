#!/usr/bin/env python3
"""產生 ES2 WebMUD 內容清單網頁：技能、武器、防具、物品、區域。

直接掃描 mudlib 原始碼（d/、obj/、custom/、daemon/skill/），整理成資料後嵌進
tools/codex_template.html，輸出一個不依賴其他檔案的網頁。

用法：
    python3 tools/build_codex.py                  # 輸出 docs/catalog/es2_catalog.html
    python3 tools/build_codex.py 其他輸出路徑.html
"""
import json
import re
import sys
from collections import defaultdict, deque
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'
TEMPLATE = ROOT / 'tools' / 'codex_template.html'
OUT = ROOT / 'docs' / 'catalog' / 'es2_catalog.html'
SCAN_DIRS = ['d', 'obj', 'custom']

# --------------------------------------------------------------------------- 名稱對照

NAMED = {  # 與 cmds/std/identify.c 相同
    'attack': '攻擊能力值', 'defense': '防禦能力值', 'str': '膂力', 'cor': '膽識', 'cps': '定力',
    'int': '悟性', 'wis': '慧根', 'spi': '靈性', 'con': '根骨', 'dex': '機敏', 'kar': '福緣',
    'damage': '傷害力', 'armor': '防禦力', 'spell': '咒文能力', 'magic_ability': '魔力',
    'gin': '精', 'kee': '氣', 'sen': '神', 'HP': '形體', 'food': '食物', 'water': '飲水',
}
SLOT = {'armor': '護甲', 'cloth': '衣服', 'head_eq': '頭部', 'neck_eq': '項鍊', 'finger_eq': '戒指',
        'waist_eq': '腰帶', 'hand_eq': '手部', 'leg_eq': '腿部', 'feet_eq': '鞋子', 'wrist_eq': '手腕'}
SLOT_ORDER = list(SLOT)
WEAPON_KIND = {'blade': '刀', 'sword': '劍', 'staff': '杖', 'axe': '斧', 'dagger': '匕首', 'pike': '槍',
               'whip': '鞭', 'blunt': '錘棒', 'needle': '針', 'throwing': '暗器'}
KIND_ORDER = list(WEAPON_KIND)
CLASS_NAME = {'soldier': '軍人', 'fighter': '武者', 'thief': '盜賊', 'taoist': '道士', 'alchemist': '方士',
              'scholar': '書生', 'monk': '和尚', 'commoner': '平民'}
RACE_NAME = {'headless': '形天族', 'human': '人類', 'malik': '巫首', 'yaksa': '夜叉', 'ashura': '阿修羅'}
DIR_AREA = {  # 沒有 map/area 的房間，依目錄給區域名稱
    'custom/oldpine': '老松林小徑', 'custom/home': '家園', 'custom/wizroom/w/windstory': '巫師房間',
}
DIRS = {  # 地圖座標：x 往東、y 往南、z 往上
    'north': (0, -1, 0), 'south': (0, 1, 0), 'east': (1, 0, 0), 'west': (-1, 0, 0),
    'northeast': (1, -1, 0), 'northwest': (-1, -1, 0), 'southeast': (1, 1, 0), 'southwest': (-1, 1, 0),
    'up': (0, 0, 1), 'down': (0, 0, -1),
}


def load_chinese():
    try:
        s = (MUD / 'data' / 'chinese.o').read_text(encoding='utf-8', errors='replace')
    except OSError:
        return {}
    return dict(re.findall(r'"([^"]*)":"([^"]*)"', s))


CHINESE = load_chinese()


def zh(key):
    return NAMED.get(key) or CHINESE.get(key) or key


# --------------------------------------------------------------------------- LPC 解析小工具

def read(p):
    return p.read_text(encoding='utf-8', errors='replace')


def strip_comments(s):
    s = re.sub(r'/\*.*?\*/', '', s, flags=re.S)
    return re.sub(r'(?m)^\s*//.*$', '', s)


def mud_path(p):
    return '/' + str(p.relative_to(MUD).with_suffix('')).replace('\\', '/')


def resolve(expr, here):
    """把 __DIR__"x"、"/d/x"、STOCK_WEAPON("x") 之類的路徑運算式轉成 /d/x。"""
    expr = expr.strip()
    base = here.rsplit('/', 1)[0] + '/'
    m = re.match(r'STOCK_(?:WEAPON|ARMOR)\(\s*"([^"]+)"\s*\)', expr)
    if m:
        return '/obj/area/obj/' + m.group(1)
    parts = re.findall(r'__DIR__|"((?:[^"\\]|\\.)*)"', expr)
    if not parts:
        return None
    out = ''
    for tok in re.finditer(r'__DIR__|"((?:[^"\\]|\\.)*)"', expr):
        out += base if tok.group(0) == '__DIR__' else tok.group(1)
    if not out.startswith('/'):
        out = base + out
    out = re.sub(r'\.c$', '', out)
    return re.sub(r'/+', '/', out)


def lpc_string(expr):
    """把 "a" "b" 或 @LONG...LONG 這類字串運算式合併成文字。"""
    m = re.match(r'\s*@(\w+)\n(.*?)\n\1', expr, re.S)
    if m:
        return m.group(2) + '\n'
    parts = re.findall(r'"((?:[^"\\]|\\.)*)"', expr)
    s = ''.join(parts)
    s = s.replace('\\n', '\n').replace('\\"', '"').replace('\\x1b', '\x1b').replace('\\t', '  ')
    return s


def set_value(src, key):
    """取 set("key", ...) 的原始運算式文字。"""
    m = re.search(r'set\(\s*"%s"\s*,' % re.escape(key), src)
    if not m:
        return None
    i, depth, j = m.end(), 1, m.end()
    in_str = False
    while j < len(src):
        c = src[j]
        if in_str:
            if c == '\\':
                j += 2
                continue
            if c == '"':
                in_str = False
        elif c == '"':
            in_str = True
        elif c == '@' and re.match(r'@(\w+)\n', src[j:]):
            tag = re.match(r'@(\w+)\n', src[j:]).group(1)
            k = src.find('\n' + tag, j + 1)
            j = k + len(tag) + 1 if k > 0 else j + 1
            continue
        elif c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
            if depth == 0:
                return src[i:j]
        j += 1
    return None


def set_int(src, key):
    v = set_value(src, key)
    if v is None:
        return None
    m = re.match(r'\s*(-?\d+)\s*$', v)
    return int(m.group(1)) if m else None


def set_str(src, key):
    v = set_value(src, key)
    return lpc_string(v) if v is not None else None


def mapping_pairs(expr):
    return [(k, int(v)) for k, v in re.findall(r'"([^"]+)"\s*:\s*(-?\d+)', expr or '')]


def path_mapping(expr, here):
    out = {}
    for m in re.finditer(r'((?:__DIR__\s*)?"[^"]*"|STOCK_\w+\(\s*"[^"]+"\s*\))\s*:\s*([^,\]]+)', expr or ''):
        p = resolve(m.group(1), here)
        if p is None:
            continue
        v = m.group(2).strip()
        out[p] = int(v) if re.fullmatch(r'-?\d+', v) else v
    return out


def name_ids(src):
    m = re.search(r'set_name\(\s*("(?:[^"\\]|\\.)*")\s*,\s*(\(\{.*?\}\)|"[^"]*")', src, re.S)
    if not m:
        m2 = re.search(r'set_name\(\s*((?:\w+\s*\+\s*)?"(?:[^"\\]|\\.)*"(?:\s*\+\s*\w+)?)', src)
        if not m2:
            return None, []
        return lpc_string(m2.group(1)), []
    return lpc_string(m.group(1)), re.findall(r'"([^"]*)"', m.group(2))


def money_text(copper):
    if copper is None:
        return None
    if copper >= 100:
        t = copper // 100
        r = copper % 100
        return f'{t} 兩' + (f' {r} 文' if r else '')
    return f'{copper} 文'


# --------------------------------------------------------------------------- 武器傷害

SETUP = {  # feature/weapon/*.c 的 setup_*()：(x, y, z, r) -> [(技能, x, y, z, r)]
    'blade': lambda x, y, z, r: [('blade', x, y, z, r), ('secondhand blade', x, y // 2, z, r), ('twohanded blade', x, y * 4 // 3, z * 3 // 2, r)],
    'sword': lambda x, y, z, r: [('sword', x, y, z, r), ('secondhand sword', x, y // 2, z, r), ('twohanded sword', x, y * 3 // 2, z * 4 // 3, r)],
    'staff': lambda x, y, z, r: [('staff', x, y, z, r), ('secondhand staff', x, y, z // 2, r), ('twohanded staff', x + 1, y * 3 // 2, z * 3 // 2, r)],
    'axe': lambda x, y, z, r: [('axe', x, y, z, r), ('secondhand axe', x, y // 2, z, r), ('twohanded axe', x, y * 2, z * 4 // 3, r)],
    'dagger': lambda x, y, z, r: [('dagger', x, y, z, r), ('secondhand dagger', x, y, z, r)],
    'pike': lambda x, y, z, r: [('pike', x, y, z, r), ('secondhand pike', x, y, z // 2, r), ('twohanded pike', x + 1, y * 4 // 3, z, r)],
    'blunt': lambda x, y, z, r: [('blunt', x, y, z, r), ('secondhand blunt', x, y, z * 2 // 3, r), ('twohanded blunt', x + 1, y, z * 2, r)],
    'whip': lambda x, y, z, r: [('whip', x, y, z, r)],
    'needle': lambda x, y, z, r: [('needle', x, y, z, r), ('secondhand needle', x, y, z, r)],
}


def weapon_damage(src):
    dmg = {}
    for m in re.finditer(r'setup_(\w+)\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*\)', src):
        kind = m.group(1)
        if kind in SETUP:
            for sk, x, y, z, r in SETUP[kind](*map(int, m.groups()[1:])):
                dmg[sk] = (x, y, z, r)
    for m in re.finditer(r'init_damage\(\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*([^;]*?)\)\s*;', src):
        for sk in re.findall(r'"([^"]+)"', m.group(5)):
            dmg[sk] = tuple(map(int, m.groups()[:4]))
    return dmg


def weapon_kind(src, wield):
    m = re.search(r'inherit\s+F_(SWORD|BLADE|BLUNT|AXE|DAGGER|NEEDLE|STAFF|PIKE|WHIP)\b', src)
    if m:
        return m.group(1).lower()
    for sk in wield:
        base = sk.split()[-1]
        if base in WEAPON_KIND:
            return base
    m = re.search(r'setup_(\w+)\(', src)
    if m and m.group(1) in WEAPON_KIND:
        return m.group(1)
    m = re.search(r'inherit\s+(SWORD|BLADE|THROWING)\b', src)
    if m:
        return m.group(1).lower()
    return 'blade'


# --------------------------------------------------------------------------- 共同屬性

def common(p, src, code):
    name, ids = name_ids(code)
    item = {
        'id': mud_path(p),
        'file': str(p.relative_to(ROOT)).replace('\\', '/'),
        'name': name or p.stem,
        'ids': ids,
        'long': (set_str(code, 'long') or '').rstrip('\n'),
    }
    w = re.search(r'set_weight\(\s*(\d+)\s*\)', code)
    item['weight'] = int(w.group(1)) if w else (set_int(code, 'base_weight') or set_int(code, 'weight'))
    v = set_int(code, 'value')
    if v is None:
        v = set_int(code, 'base_value')
    item['value'] = money_text(v) if v is not None else None
    item['unit'] = set_str(code, 'unit')
    flags = []
    if 'F_UNIQUE' in code:
        flags.append('唯一')
    poison = re.search(r'CONDITION_D\("([^"]+)"\)->poison|/daemon/condition/(\w+)"\s*->\s*poison', code)
    if poison:
        flags.append('劇毒')
        item['poison'] = poison.group(1) or poison.group(2)
    if 'miss_ob' in code:
        flags.append('特攻')
    for c in re.findall(r'query_class\(\)\s*!=\s*"(\w+)"', code):
        flags.append('限' + CLASS_NAME.get(c, c))
    for r in re.findall(r'query_race\(\)\s*!=\s*"(\w+)"', code):
        flags.append('限' + RACE_NAME.get(r, r))
    if 'F_STUDY' in code:
        flags.append('可研讀')
    verbs = re.findall(r'add_action\(\s*"\w+"\s*,\s*"([\w ]+)"\s*\)', code)
    if verbs:
        item['verbs'] = verbs
    item['flags'] = flags
    return item


def traits(code, prefix):
    out = {}
    for m in re.finditer(r'set\(\s*"%s/([^"]+)"\s*,\s*\(\[(.*?)\]\)\s*\)' % prefix, code, re.S):
        out[m.group(1)] = [[zh(k), v, k] for k, v in mapping_pairs(m.group(2))]
    for m in re.finditer(r'set\(\s*"%s/([^"/]+)/([^"]+)"\s*,\s*(-?\d+)\s*\)' % prefix, code):
        out.setdefault(m.group(1), []).append([zh(m.group(2)), int(m.group(3)), m.group(2)])
    return out


# --------------------------------------------------------------------------- 各類物件

ROOM_INHERIT = re.compile(r'inherit\s+(ROOM|BANK|HOCKSHOP|INN|TEMPLE|"/std/room[^"]*")')
NPC_INHERIT = re.compile(r'inherit\s+(NPC|F_VILLAGER|F_VENDOR|F_FIGHTER|F_SOLDIER|F_BANDIT|F_TRAINER|F_TEACHER|"/custom/ghost/std_ghost"|"/std/char/npc")')
WEAPON_INHERIT = re.compile(r'inherit\s+(F_(SWORD|BLADE|BLUNT|AXE|DAGGER|NEEDLE|STAFF|PIKE|WHIP)|SWORD|BLADE|THROWING)\b')
ARMOR_INHERIT = re.compile(r'inherit\s+(F_(ARMOR|CLOTH|HEAD_EQ|HAND_EQ|FEET_EQ|NECK_EQ|FINGER_EQ|WAIST_EQ|LEG_EQ|WRIST_EQ)|CLOTH|EQUIP)\b')


def classify(code):
    if ROOM_INHERIT.search(code) or (re.search(r'set\(\s*"exits"', code) and re.search(r'set\(\s*"short"', code) and 'set_name' not in code):
        return 'room'
    if NPC_INHERIT.search(code) or re.search(r'set_race\(', code):
        return 'npc'
    if WEAPON_INHERIT.search(code) or re.search(r'init_damage\(|setup_(sword|blade|blunt|axe|dagger|needle|staff|pike|whip)\(', code):
        return 'weapon'
    if ARMOR_INHERIT.search(code) or set_value(code, 'wear_as') is not None:
        return 'armor'
    if 'set_name' in code:
        return 'item'
    return None


def parse_weapon(p, src, code):
    it = common(p, src, code)
    wv = set_value(code, 'wield_as')
    wield = re.findall(r'"([^"]+)"', wv) if wv else []
    dmg = weapon_damage(code)
    if not wield:
        wield = list(dmg)
    it['kind'] = weapon_kind(code, wield)
    rows = []
    for sk in wield:
        d = dmg.get(sk)
        row = {'skill': zh(sk), 'code': sk}
        if d:
            x, y, z, r = d
            row['dmg'] = f'{r + x} - {r + x * y}'
            row['bonus'] = f'{z}%'
            row['mult'] = x
        rows.append(row)
    it['usages'] = rows
    it['traits'] = {zh(k): v for k, v in traits(code, 'apply_weapon').items()}
    if not dmg:
        m = re.search(r'init_(blade|sword|throwing)\(\s*(\d+)\s*\)', code)
        if m:
            it['usages'] = [{'skill': zh(m.group(1)), 'code': m.group(1), 'dmg': f'基礎 {m.group(2)}'}]
    return it


def parse_armor(p, src, code):
    it = common(p, src, code)
    wv = set_value(code, 'wear_as')
    slots = re.findall(r'"([^"]+)"', wv) if wv else []
    tr = traits(code, 'apply_armor')
    if not slots:
        slots = list(tr)
    if not slots:
        m = re.search(r'inherit\s+F_(ARMOR|CLOTH|HEAD_EQ|HAND_EQ|FEET_EQ|NECK_EQ|FINGER_EQ|WAIST_EQ|LEG_EQ|WRIST_EQ)', code)
        slots = [m.group(1).lower()] if m else ['armor']
    it['slot'] = slots[0] if slots[0] in SLOT else 'armor'
    it['traits'] = {SLOT.get(k, k): v for k, v in tr.items()}
    return it


def stat_effects(code):
    eff = []
    for fn, st, n in re.findall(r'(supplement_stat|consume_stat|damage_stat|heal_stat)\(\s*"(\w+)"\s*,\s*(-?\d+)', code):
        label = zh(st)
        if fn == 'supplement_stat' or fn == 'heal_stat':
            eff.append(f'{label} +{n}')
        elif fn == 'consume_stat':
            eff.append(f'{label} -{n}')
        else:
            eff.append(f'{label}實格 -{n}')
    return eff


def item_category(p, code):
    rel = str(p.relative_to(MUD))
    if 'F_FOOD' in code or set_int(code, 'food_stuff') or 'food_remaining' in code:
        return '食物'
    if 'F_LIQUID' in code or 'liquid' in code:
        return '飲品'
    if '/drug/' in rel or '/medication/' in rel or 'pill' in rel or re.search(r'"(pill|drug|herb|medicine)"', code) or '丹' in (name_ids(code)[0] or ''):
        return '丹藥'
    if 'F_STUDY' in code or '/books/' in rel:
        return '書籍'
    if '/money/' in rel or 'MONEY' in code:
        return '錢幣'
    if 'CONTAINER' in code:
        return '容器'
    return '其他'


def parse_item(p, src, code):
    it = common(p, src, code)
    it['cat'] = item_category(p, code)
    eff = stat_effects(code)
    fs = set_int(code, 'food_stuff')
    if fs:
        eff.insert(0, f'食物 +{fs}')
    if eff:
        it['effects'] = eff
    content = set_value(code, 'content')
    if content:
        it['study'] = [[zh(k), v] for k, v in mapping_pairs(content)]
    return it


def parse_npc(p, src, code):
    it = common(p, src, code)
    it['race'] = (re.search(r'set_race\(\s*"(\w+)"', code) or [None, None])[1]
    it['class'] = (re.search(r'set_class\(\s*"(\w+)"', code) or [None, None])[1]
    lv = re.search(r'set_level\(\s*(\d+)', code)
    it['level'] = int(lv.group(1)) if lv else None
    it['gender'] = set_str(code, 'gender')
    it['title'] = set_str(code, 'title')
    eq = []
    for m in re.finditer(r'carry_object\(\s*([^;]*?)\)\s*(->\s*(wield|wear)\(([^)]*)\))?\s*;', code):
        path = resolve(m.group(1), it['id'])
        if path:
            eq.append({'path': path, 'use': m.group(3) or ''})
    it['equip'] = eq
    skills = [[zh(k), int(v), k] for k, v in re.findall(r'set_skill\(\s*"([^"]+)"\s*,\s*(\d+)', code)]
    it['skills'] = skills
    it['wander'] = 'random_move' in code
    it['ghost'] = 'std_ghost' in code
    return it


def parse_room(p, src, code):
    rid = mud_path(p)
    ex = {}
    ev = set_value(code, 'exits') or ''
    for m in re.finditer(r'"([^"]+)"\s*:\s*((?:__DIR__\s*)?"[^"]*"|STOCK_\w+\([^)]*\))', ev):
        t = resolve(m.group(2), rid)
        if t:
            ex[m.group(1)] = t
    return {
        'id': rid,
        'file': str(p.relative_to(ROOT)).replace('\\', '/'),
        'short': re.sub(r'\x1b\[[0-9;]*m', '', set_str(code, 'short') or p.stem),
        'long': (set_str(code, 'long') or '').rstrip('\n'),
        'exits': ex,
        'objects': path_mapping(set_value(code, 'objects'), rid),
        'area': set_str(code, 'map/area'),
        'layer': set_str(code, 'map/layer'),
    }


# --------------------------------------------------------------------------- 技能

def parse_skills(used_codes):
    base = read(MUD / 'feature' / 'char' / 'skill.c')
    restored = set(re.findall(r'skill\s*==\s*"([^"]+)"', base.split('int uses_restored_skill_threshold', 1)[1].split('return 0;', 1)[0]))
    caps = {k: int(v) for k, v in re.findall(r'skill\s*==\s*"([^"]+)"[^)]*\)\s*return\s*(\d+)', base.split('int restored_skill_cap', 1)[1].split('}', 1)[0])}
    formula = ('升級所需累積點數 = 等級² × 基數；基數：1–60 級 100、61–90 級 125、91–120 級 150、'
               '121–160 級 175、161–180 級 200、181 級以上 250。')
    reg = {}
    doc = ROOT / 'docs' / 'SKILL_NAMES.md'
    if doc.exists():
        for cat, name, code in re.findall(r'^\| ([^|]+) \| ([^|]+) \| `([^`]+)` \|', read(doc), re.M):
            if cat.strip() in ('分類',):
                continue
            reg[code] = (cat.strip(), name.strip())
    skills = {}
    for p in sorted((MUD / 'daemon' / 'skill').glob('*.c')):
        src = read(p)
        code = p.stem.replace('_', ' ') if ' ' not in p.stem and p.stem in ('secondhand_axe',) else p.stem
        m = re.search(r'register_skill_daemon\("([^"]+)"\)', src)
        if m:
            code = m.group(1)
        elif '_' in p.stem and p.stem.split('_')[0] in ('secondhand', 'twohanded'):
            code = p.stem.replace('_', ' ')
        desc = re.search(r'description:\s*(.+)', src)
        typ = re.search(r'string type\(\)\s*\{\s*return\s*"(\w+)"', src)
        notes = [c.strip() for c in re.findall(r'/\*(.*?)\*/', src, re.S)
                 if re.search(r'gin|kee|sen|STR|COR|CON|INT|growth|成長|threshold|升級', c) and 'description:' not in c]
        grow = []
        for st, n in re.findall(r'advance_stat\(\s*"(\w+)"\s*,\s*(\d+)', src):
            grow.append(f'{zh(st)} +{n}')
        thr = re.search(r'(private\s+)?int\s+\w*threshold\w*\([^)]*\)\s*\{.*?\n\}', src, re.S)
        if thr:
            form = '依技能程式：\n' + thr.group(0).strip()
        elif code in restored or 'apply_restored_skill_progression' in src:
            form = formula + f' 上限 {caps.get(code, 200)} 級。'
        else:
            form = '沒有自動升級規則（由學習、研讀或劇情提升）。'
        skills[code] = {
            'code': code, 'name': zh(code), 'impl': True,
            'cat': reg.get(code, ('', ''))[0] or ({'spell': '法術', 'martial': '武學'}.get(typ.group(1), typ.group(1)) if typ else ''),
            'desc': desc.group(1).strip() if desc else '',
            'formula': form, 'growth': sorted(set(grow)), 'notes': notes,
            'file': str(p.relative_to(ROOT)).replace('\\', '/'),
        }
    for code in sorted(set(reg) | used_codes):
        if code in skills:
            if code in reg and not skills[code]['cat']:
                skills[code]['cat'] = reg[code][0]
            continue
        skills[code] = {'code': code, 'name': reg.get(code, ('', zh(code)))[1] or zh(code), 'impl': False,
                        'cat': reg.get(code, ('', ''))[0], 'desc': '', 'formula': '尚未實作（目前只有代碼與名稱）。',
                        'growth': [], 'notes': [], 'file': ''}
    return sorted(skills.values(), key=lambda s: (not s['impl'], s['cat'] or '~', s['code']))


# --------------------------------------------------------------------------- 地圖座標

def layout(rooms, ids):
    """依出口方向替區域內的房間排座標；衝突時往旁邊找空位。"""
    pos = {}
    used = set()
    comp_x = 0
    ids = sorted(ids)
    order = sorted(ids, key=lambda r: (-len(rooms[r]['exits']), r))
    for start in order:
        if start in pos:
            continue
        q = deque([start])
        cx = comp_x
        pos[start] = (cx, 0, 0)
        used.add(pos[start])
        comp = [start]
        while q:
            cur = q.popleft()
            x, y, z = pos[cur]
            for d, t in sorted(rooms[cur]['exits'].items()):
                if t not in ids or t in pos:
                    continue
                dx, dy, dz = DIRS.get(d, (0, 0, 0))
                if (dx, dy, dz) == (0, 0, 0):
                    dx = 1
                cand = (x + dx, y + dy, z + dz)
                if cand in used:
                    for r in range(1, 6):
                        found = None
                        for ox in range(-r, r + 1):
                            for oy in range(-r, r + 1):
                                c = (cand[0] + ox, cand[1] + oy, cand[2])
                                if c not in used:
                                    found = c
                                    break
                            if found:
                                break
                        if found:
                            cand = found
                            break
                pos[t] = cand
                used.add(cand)
                comp.append(t)
                q.append(t)
        xs = [pos[r][0] for r in comp]
        comp_x = max(xs) + 2
    return pos


# --------------------------------------------------------------------------- 主程式

def main(out):
    weapons, armors, items, npcs, rooms = [], [], [], {}, {}
    for d in SCAN_DIRS:
        for p in sorted((MUD / d).rglob('*.c')):
            src = read(p)
            code = strip_comments(src)
            kind = classify(code)
            try:
                if kind == 'room':
                    r = parse_room(p, src, code)
                    rooms[r['id']] = r
                elif kind == 'npc':
                    n = parse_npc(p, src, code)
                    npcs[n['id']] = n
                elif kind == 'weapon':
                    weapons.append(parse_weapon(p, src, code))
                elif kind == 'armor':
                    armors.append(parse_armor(p, src, code))
                elif kind == 'item':
                    items.append(parse_item(p, src, code))
            except Exception as e:  # 單一檔案解析失敗不影響整體
                print('skip', p, e, file=sys.stderr)

    # 區域：有 map/area 的依名稱分組，沒有的依所在目錄
    areas = defaultdict(list)
    for rid in [r for r in rooms if r.startswith('/obj/')]:  # 系統用的空房間，不是地圖
        del rooms[rid]
    for r in rooms.values():
        key = r['area'] or DIR_AREA.get(r['id'].rsplit('/', 2)[0].lstrip('/'), r['id'].rsplit('/', 2)[0].lstrip('/'))
        r['areaKey'] = key
        areas[key].append(r['id'])
    npc_rooms = defaultdict(list)
    item_rooms = defaultdict(list)
    for r in rooms.values():
        for path, n in r['objects'].items():
            if path in npcs:
                npc_rooms[path].append([r['id'], n])
            else:
                item_rooms[path].append([r['id'], n])
    for n in npcs.values():
        n['rooms'] = npc_rooms.get(n['id'], [])
    area_list = []
    for key, ids in areas.items():
        pos = layout(rooms, set(ids))
        for rid in ids:
            rooms[rid]['pos'] = pos[rid]
        npc_ids = sorted({p for rid in ids for p in rooms[rid]['objects'] if p in npcs})
        area_list.append({'key': key, 'name': key, 'rooms': sorted(ids), 'npcs': npc_ids})
    area_list.sort(key=lambda a: -len(a['rooms']))

    # 技能清單：技能程式、docs/SKILL_NAMES.md，加上武器用法、裝備特性與 NPC 用到的技能代碼
    not_skill = set(NAMED) | {'intimidate', 'wittiness', 'awarness', 'move', 'vision_of_ghost', 'resist_poison'}
    used_codes = set()
    for w in weapons:
        used_codes.update(u['code'] for u in w['usages'])
    for coll in (weapons, armors):
        for it in coll:
            for lst in it['traits'].values():
                used_codes.update(k for _, _, k in lst)
    for n in npcs.values():
        used_codes.update(k for _, _, k in n['skills'])
    skills = parse_skills({c for c in used_codes if c and c not in not_skill and not c.startswith(('armor_vs', 'damage_vs'))})
    data = {
        'skills': skills,
        'weapons': sorted(weapons, key=lambda w: (KIND_ORDER.index(w['kind']) if w['kind'] in KIND_ORDER else 99, w['id'])),
        'armors': sorted(armors, key=lambda a: (SLOT_ORDER.index(a['slot']) if a['slot'] in SLOT_ORDER else 99, a['id'])),
        'items': sorted(items, key=lambda i: (i['cat'], i['id'])),
        'npcs': npcs,
        'rooms': rooms,
        'areas': area_list,
        'itemRooms': item_rooms,
        'weaponKinds': WEAPON_KIND,
        'slots': SLOT,
        'counts': {'skills': len(skills), 'weapons': len(weapons), 'armors': len(armors), 'items': len(items),
                   'npcs': len(npcs), 'rooms': len(rooms), 'areas': len(area_list)},
    }
    blob = json.dumps(data, ensure_ascii=False, separators=(',', ':')).replace('</', '<\\/')
    html = read(TEMPLATE).replace('/*__CATALOG_DATA__*/null', blob, 1)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(html, encoding='utf-8')
    print(json.dumps(data['counts'], ensure_ascii=False), '->', out)


if __name__ == '__main__':
    main(Path(sys.argv[1]) if len(sys.argv) > 1 else OUT)
