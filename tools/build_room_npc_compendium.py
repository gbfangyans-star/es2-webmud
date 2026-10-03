#!/usr/bin/env python3
"""Build a human-readable compendium of rooms (by area) with their NPCs.

Reads LPC sources under source/upstream/mudlib and writes
docs/ROOM_NPC_COMPENDIUM.md plus catalog/room_npc_compendium.json.

Output mimics in-game `look` output:

    紅燈客棧 -
        <long description>
        這裡唯一的出口是 west。
      靈雲觀道士 公孫志(Gong-sun zhi)

and, for each NPC, the `look <npc>` text (long, race/age line, carried items).
"""
import json
import os
import re
import sys
from collections import OrderedDict, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MUDLIB = os.path.join(ROOT, "source", "upstream", "mudlib")

ROOM_DIRS = [
    "d/snow", "d/lee", "d/oldpine", "d/wutang",
    "custom/zhenwu/room", "custom/home/room", "custom/wizroom",
    "adm/guild",
]

DIR_AREA = {
    "d/snow": "雪亭鎮",
    "d/lee": "李家村",
    "d/oldpine": "老松林",
    "d/wutang": "五堂鎮",
    "custom/zhenwu": "振武軍營",
    "custom/home": "玩家住宅",
    "custom/wizroom": "巫師工作室",
    "adm/guild": "公會",
}

AREA_ORDER = ["雪亭鎮", "李家村", "五堂鎮", "老松林", "迷霧森林", "振武軍營",
              "玩家住宅", "公會", "巫師工作室"]

RACE_ZH = {
    "human": "人類", "beast": "野獸", "blackteeth": "黑齒", "yenhold": "厭火",
    "woochan": "無腸", "avatar": "人類", "dingling": "丁零", "headless": "刑天",
    "jiaojao": "焦僥", "rainner": "雨師", "yaksa": "夜叉", "malik": "馬立克",
    "ashura": "阿修羅",
}

CN_DIGITS = "零一二三四五六七八九"


def chinese_number(n):
    if n < 10:
        return CN_DIGITS[n]
    if n < 100:
        t, o = divmod(n, 10)
        return ("" if t == 1 else CN_DIGITS[t]) + "十" + (CN_DIGITS[o] if o else "")
    for unit, name in ((10000, "萬"), (1000, "千"), (100, "百")):
        if n >= unit:
            h, r = divmod(n, unit)
            s = chinese_number(h) + name
            if r == 0:
                return s
            if r < unit // 10:
                s += "零"
            return s + (chinese_number(r) if r >= 10 or r < unit // 10 else CN_DIGITS[r])

# ---------------------------------------------------------------- LPC lexing

def strip_comments(src):
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if src.startswith("@", i) and re.match(r"@([A-Z_]+)", src[i:]):
            m = re.match(r"@([A-Z_]+)\n?", src[i:])
            tag = m.group(1)
            end = src.find("\n" + tag, i + m.end() - 1)
            if end < 0:
                end = n
            j = end + len(tag) + 1
            out.append(src[i:j])
            i = j
        elif c == '"':
            j = i + 1
            while j < n and src[j] != '"':
                j += 2 if src[j] == "\\" else 1
            out.append(src[i:j + 1])
            i = j + 1
        elif c == "'" and i + 2 < n and (src[i + 2] == "'" or src[i + 1] == "\\"):
            j = src.find("'", i + 2 if src[i + 1] == "\\" else i + 1)
            out.append(src[i:j + 1])
            i = j + 1
        elif src.startswith("//", i):
            j = src.find("\n", i)
            i = n if j < 0 else j
        elif src.startswith("/*", i):
            j = src.find("*/", i + 2)
            i = n if j < 0 else j + 2
        else:
            out.append(c)
            i += 1
    return "".join(out)


def unescape(s):
    return (s.replace("\\n", "\n").replace('\\"', '"').replace("\\t", "\t")
            .replace("\\\\", "\\"))


STR_TOKEN = r'(?:"(?:[^"\\]|\\.)*"|__DIR__|[A-Z][A-Z0-9_]*)'
STR_EXPR = r'(?:@(?P<tag>[A-Z_]+)\n?(?P<here>.*?)\n(?P=tag)|(?P<strs>\s*' + STR_TOKEN + r'(?:\s*\+?\s*' + STR_TOKEN + r')*))'


def parse_string_expr(expr):
    """Parse a concatenation of string literals / __DIR__."""
    expr = expr.strip()
    m = re.match(r"@([A-Z_]+)\n?(.*?)\n\1", expr, re.S)
    if m:
        return m.group(2) + "\n"
    parts = re.findall(r'"((?:[^"\\]|\\.)*)"|(__DIR__)', expr)
    if not parts:
        return None
    return "".join("\x00DIR\x00" if d else unescape(s) for s, d in parts)


def find_set(src, key):
    """Return the raw string value of set("key", <string>)."""
    pat = re.compile(r'set\s*\(\s*"' + re.escape(key) + r'"\s*,\s*' + STR_EXPR + r"\s*\)", re.S)
    m = pat.search(src)
    if not m:
        return None
    if m.group("tag"):
        return m.group("here") + "\n"
    return parse_string_expr(m.group("strs"))


def find_set_int(src, key):
    m = re.search(r'set\s*\(\s*"' + re.escape(key) + r'"\s*,\s*(\d+)\s*\)', src)
    return int(m.group(1)) if m else None


def extract_mapping(src, key):
    """Return list of (key_expr, value_expr) from set("key", ([ ... ]))."""
    m = re.search(r'set\s*\(\s*"' + re.escape(key) + r'"\s*,\s*\(\[', src)
    if not m:
        return None
    i, depth = m.end(), 1
    start = i
    while i < len(src) and depth:
        if src[i] == '"':
            j = i + 1
            while src[j] != '"':
                j += 2 if src[j] == "\\" else 1
            i = j + 1
            continue
        if src.startswith("([", i) or src.startswith("({", i):
            depth += 1
            i += 2
            continue
        if src.startswith("])", i) or src.startswith("})", i):
            depth -= 1
            i += 2
            continue
        i += 1
    body = src[start:i - 2]
    pairs = []
    for ent in re.finditer(r'((?:\s*(?:"(?:[^"\\]|\\.)*"|__DIR__|[A-Z_]+))+)\s*:\s*([^,]+?)\s*(?:,|$)', body, re.S):
        pairs.append((ent.group(1).strip(), ent.group(2).strip()))
    return pairs


def resolve_path(expr, base_dir, defines):
    for k, v in defines.items():
        expr = re.sub(r"\b" + k + r"\b", v, expr)
    s = parse_string_expr(expr)
    if s is None:
        return None
    s = s.replace("\x00DIR\x00", "/" + base_dir + "/")
    if not s.startswith("/"):
        s = "/" + base_dir + "/" + s
    s = re.sub(r"/+", "/", s)
    if s.endswith(".c"):
        s = s[:-2]
    return s


def file_defines(src):
    d = {}
    for m in re.finditer(r'^#define\s+([A-Z_]+)\s+(.+)$', src, re.M):
        d[m.group(1)] = m.group(2).strip()
    return d


def read_src(path):
    with open(path, encoding="utf-8", errors="replace") as f:
        return f.read()


def lpc_file(objpath):
    p = os.path.join(MUDLIB, objpath.lstrip("/"))
    if not p.endswith(".c"):
        p += ".c"
    return p if os.path.exists(p) else None


# ---------------------------------------------------------------- objects

NAME_RE = re.compile(r'set_name\s*\(\s*(' + STR_TOKEN + r'(?:\s*' + STR_TOKEN + r')*)\s*,\s*(?:\(\{\s*)?"((?:[^"\\]|\\.)*)"')
CARRY_RE = re.compile(r'carry_object\s*\(\s*(?:STOCK_[A-Z]+\s*\(\s*"(?P<stock>[^"]+)"\s*\)'
                      r'|(?P<expr>(?:\s*(?:"(?:[^"\\]|\\.)*"|__DIR__))+))\s*\)\s*(?:->\s*(?P<act>wear|wield)\s*\()?')


def parse_name(src):
    m = NAME_RE.search(src)
    if not m:
        return None
    return parse_string_expr(m.group(1)) or "", m.group(2)


_item_cache = {}


def item_info(objpath):
    if objpath in _item_cache:
        return _item_cache[objpath]
    f = lpc_file(objpath)
    info = None
    if f:
        src = strip_comments(read_src(f))
        nm = parse_name(src)
        if nm:
            info = {"name": nm[0], "id": nm[1]}
    _item_cache[objpath] = info
    return info


def is_npc_source(src):
    return bool(re.search(r"\b(set_race|set_class|F_VILLAGER|F_FIGHTER|F_VENDOR|F_SOLDIER|"
                          r"F_BANDIT|F_SCHOLAR|F_TRAVELER|std_ghost|inherit\s+NPC|CHARACTER)\b", src))


_npc_cache = {}


def npc_info(objpath):
    if objpath in _npc_cache:
        return _npc_cache[objpath]
    f = lpc_file(objpath)
    if not f:
        _npc_cache[objpath] = None
        return None
    raw = read_src(f)
    src = strip_comments(raw)
    if not is_npc_source(src):
        _npc_cache[objpath] = None
        return None
    base_dir = os.path.dirname(objpath.lstrip("/"))
    info = {"path": objpath}
    nm = parse_name(src)
    info["name"] = nm[0] if nm else os.path.basename(objpath)
    info["id"] = nm[1] if nm else ""
    for k in ("title", "nickname", "gender", "long"):
        v = find_set(src, k)
        if v is not None:
            info[k] = v
    info["age"] = find_set_int(src, "age")
    m = re.search(r'set_race\s*\(\s*"([^"]+)"', src)
    info["race"] = m.group(1) if m else None
    m = re.search(r'set_class\s*\(\s*"([^"]+)"', src)
    info["class"] = m.group(1) if m else None
    m = re.search(r"set_level\s*\(\s*(\d+)", src)
    info["level"] = int(m.group(1)) if m else None
    inv = []
    for cm in CARRY_RE.finditer(src):
        if cm.group("stock"):
            p = "/obj/area/obj/" + cm.group("stock")
        else:
            p = resolve_path(cm.group("expr"), base_dir, {})
        it = item_info(p) if p else None
        inv.append({"path": p, "name": it["name"] if it else None,
                    "id": it["id"] if it else None, "equipped": bool(cm.group("act"))})
    info["inventory"] = inv
    _npc_cache[objpath] = info
    return info


def npc_short(n):
    title = n.get("title")
    nick = n.get("nickname")
    s = (title or "") + (("「" + nick + "」") if nick else (" " if title else ""))
    return s + n["name"] + "(" + n["id"][:1].upper() + n["id"][1:] + ")"


def npc_look(n):
    lines = []
    long = n.get("long")
    if long:
        lines.append(long.rstrip("\n"))
    else:
        lines.append(n["name"] + "看起來沒有什麼特別。")
    race = n.get("race") or "human"
    humanoid = race != "beast"
    age = n.get("age")
    if humanoid and age is not None:
        pro = "她" if n.get("gender") == "female" else "他"
        age_s = ("約" + chinese_number(age // 10 * 10) + "多歲") if age > 10 else "不到十歲"
        lines.append("%s屬於%s族。%s的外表看起來%s。"
                     % (n["name"], RACE_ZH.get(race, race), pro, age_s))
    if n["inventory"]:
        pro = "她" if n.get("gender") == "female" else "他"
        lines.append(pro + "身上帶著﹕")
        for it in n["inventory"]:
            mark = "Ｖ" if it["equipped"] else "  "
            if it["name"]:
                idc = it["id"][:1].upper() + it["id"][1:]
                lines.append("%s%s (%s)" % (mark, it["name"], idc))
            else:
                lines.append("%s(未知物品 %s)" % (mark, it["path"]))
    return "\n".join(lines)


# ---------------------------------------------------------------- rooms

def is_room_source(src):
    return bool(re.search(r"inherit\s+(ROOM|INN|BANK|HOCKSHOP|TEMPLE|JOURNEY|\"/std/room)", src))


def area_for(relpath, src):
    v = find_set(src, "map/area")
    if v:
        return v
    for d, a in DIR_AREA.items():
        if relpath.startswith(d):
            return a
    return "其他"


def exits_line(exits):
    dirs = list(exits.keys())
    if not dirs:
        return "這裡沒有任何明顯的出路。"
    if len(dirs) == 1:
        return "這裡唯一的出口是 %s。" % dirs[0]
    return "這裡明顯的出口有 %s 和 %s。" % ("、".join(dirs[:-1]), dirs[-1])


def wrap_long(text):
    return "\n".join("    " + ln if i == 0 else ln
                     for i, ln in enumerate(text.rstrip("\n").split("\n")))


def parse_room(relpath):
    raw = read_src(os.path.join(MUDLIB, relpath))
    src = strip_comments(raw)
    if not is_room_source(src):
        return None
    short = find_set(src, "short")
    long = find_set(src, "long")
    if short is None and long is None:
        return None
    base_dir = os.path.dirname(relpath)
    defines = file_defines(src)
    exits = OrderedDict()
    for k, v in extract_mapping(src, "exits") or []:
        ks = parse_string_expr(k)
        tgt = resolve_path(v, base_dir, defines)
        if ks:
            exits[ks] = tgt
    objects = []
    for k, v in extract_mapping(src, "objects") or []:
        p = resolve_path(k, base_dir, defines)
        cnt = int(v) if v.isdigit() else 1
        if p:
            objects.append((p, cnt))
    # NPCs spawned in code rather than via "objects"
    for m in re.finditer(r"new\s*\(\s*((?:\s*(?:\"(?:[^\"\\]|\\.)*\"|__DIR__))+)\s*\)", src):
        p = resolve_path(m.group(1), base_dir, defines)
        if p and p not in [o[0] for o in objects] and npc_info(p):
            objects.append((p, 1))
    npcs, items = [], []
    for p, cnt in objects:
        n = npc_info(p)
        if n:
            npcs.append((n, cnt))
        else:
            it = item_info(p)
            items.append({"path": p, "name": it["name"] if it else None, "count": cnt})
    return {
        "file": "/" + relpath[:-2],
        "area": area_for(relpath, src),
        "short": (short or "").replace("\x00DIR\x00", ""),
        "long": (long or "").replace("\x00DIR\x00", ""),
        "exits": exits,
        "npcs": npcs,
        "items": items,
    }


def collect_rooms():
    rooms = []
    for d in ROOM_DIRS:
        full = os.path.join(MUDLIB, d)
        for dp, dn, fn in os.walk(full):
            dn[:] = sorted(x for x in dn if x not in ("npc", "obj", "skill"))
            for f in sorted(fn):
                if f.endswith(".c"):
                    rel = os.path.relpath(os.path.join(dp, f), MUDLIB)
                    r = parse_room(rel)
                    if r:
                        rooms.append(r)
    return rooms


def main():
    rooms = collect_rooms()
    by_area = defaultdict(list)
    for r in rooms:
        by_area[r["area"]].append(r)
    areas = [a for a in AREA_ORDER if a in by_area] + sorted(a for a in by_area if a not in AREA_ORDER)

    all_npcs = OrderedDict()
    md = ["# 房間與 NPC 敘述整理", "",
          "> 由 `tools/build_room_npc_compendium.py` 自 `source/upstream/mudlib` 原始碼自動產生，請勿手動修改。",
          "> 房間格式比照遊戲內 `look`；NPC 敘述比照 `look <npc>`（種族/年齡句為依原始碼推算的靜態版本，",
          "> 遊戲中的種族外觀描述為動態產生，此處省略）。", "",
          "## 總覽", "", "| 區域 | 房間數 | 有 NPC 的房間 | NPC 種類 |", "|---|---:|---:|---:|"]
    for a in areas:
        rs = by_area[a]
        kinds = {n["path"] for r in rs for n, _ in r["npcs"]}
        md.append("| %s | %d | %d | %d |" % (a, len(rs), sum(1 for r in rs if r["npcs"]), len(kinds)))
    md.append("| **合計** | **%d** | **%d** | **%d** |" % (
        len(rooms), sum(1 for r in rooms if r["npcs"]),
        len({n["path"] for r in rooms for n, _ in r["npcs"]})))
    md.append("")

    for a in areas:
        md += ["## %s" % a, ""]
        for r in by_area[a]:
            md.append("### %s `%s`" % (r["short"] or "(無 short)", r["file"]))
            md.append("")
            md.append("```text")
            md.append("%s -" % r["short"])
            md.append(wrap_long(r["long"]) if r["long"] else "    (無房間敘述)")
            md.append("    " + exits_line(r["exits"]))
            for n, cnt in r["npcs"]:
                for _ in range(cnt):
                    md.append("  " + npc_short(n))
            md.append("```")
            md.append("")
            if r["npcs"]:
                md.append("**NPC 敘述：**")
                md.append("")
                seen = set()
                for n, cnt in r["npcs"]:
                    all_npcs.setdefault(n["path"], {"npc": n, "rooms": []})["rooms"].append(
                        "%s（%s）" % (r["short"], a))
                    if n["path"] in seen:
                        continue
                    seen.add(n["path"])
                    md.append("- **%s** `%s`%s" % (npc_short(n), n["path"],
                                                     " ×%d" % cnt if cnt > 1 else ""))
                    md.append("")
                    md.append("  ```text")
                    for ln in npc_look(n).split("\n"):
                        md.append("  " + ln)
                    md.append("  ```")
                    md.append("")

    # NPC index
    md += ["## NPC 索引", "", "| NPC | 檔案 | 出現房間 |", "|---|---|---|"]
    for p, e in sorted(all_npcs.items()):
        md.append("| %s | `%s` | %s |" % (npc_short(e["npc"]), p, "、".join(OrderedDict.fromkeys(e["rooms"]))))
    md.append("")

    out_md = os.path.join(ROOT, "docs", "ROOM_NPC_COMPENDIUM.md")
    with open(out_md, "w", encoding="utf-8") as f:
        f.write("\n".join(md))

    js = []
    for r in rooms:
        js.append({
            "file": r["file"], "area": r["area"], "short": r["short"], "long": r["long"],
            "exits": r["exits"],
            "npcs": [{"path": n["path"], "count": c, "display": npc_short(n),
                      "name": n["name"], "id": n["id"], "title": n.get("title"),
                      "nickname": n.get("nickname"), "race": n.get("race"), "age": n.get("age"),
                      "long": n.get("long"), "look": npc_look(n),
                      "inventory": n["inventory"]} for n, c in r["npcs"]],
        })
    out_js = os.path.join(ROOT, "catalog", "room_npc_compendium.json")
    with open(out_js, "w", encoding="utf-8") as f:
        json.dump(js, f, ensure_ascii=False, indent=2)
    print("rooms=%d areas=%d npcs=%d -> %s" % (len(rooms), len(areas), len(all_npcs),
                                              os.path.relpath(out_md, ROOT)))


if __name__ == "__main__":
    sys.exit(main())
