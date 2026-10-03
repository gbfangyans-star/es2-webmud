from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'


def table(src, name):
    body = src.split('private mapping %s = ([' % name, 1)[1].split(']);', 1)[0]
    return {k: dict((a, int(b)) for a, b in re.findall(r'"(\w+)": (-?\d+)', v))
            for k, v in re.findall(r'"([^"]+)": \(\[ (.*?) \]\),', body)}


def test_affix_tables_match_design():
    src = (MUD / 'adm/daemons/enhanced.c').read_text(encoding='utf-8')
    pre, suf = table(src, 'AFFIX_PREFIX'), table(src, 'AFFIX_SUFFIX')
    assert len(pre) == 36 and len(suf) == 9
    assert pre['黑鋼'] == {'damage': 15, 'attack': 10}
    assert pre['碧血'] == {'cps': 1, 'armor': 15}
    assert pre['修羅'] == {'cor': 2, 'intimidate': 15}
    assert pre['雛鐵'] == {'attack': 10, 'force': 10}
    assert suf['天鷹'] == {'awarness': 50} and suf['金鷹'] == {'wittiness': 30}
    # 必須有前綴才會有後綴；機率 60／30／10。
    assert 'if( r >= 60 ) affix["prefix"]' in src and 'if( r >= 90 ) affix["suffix"]' in src
    assert 'if( !prefix || !stringp(suffix)' in src
    assert '#define AFFIX_COLOR 1' in src


def test_all_area_weapons_roll_on_creation():
    for f in ('longsword', 'shortsword', 'blade', 'glaive', 'bastardsword', 'broadsword', 'greatsword',
              'curved_blade', 'weirblade', 'broadaxe', 'pike', 'rod'):
        s = (MUD / 'obj/area/obj' / (f + '.c')).read_text(encoding='utf-8')
        assert 'if( clonep() ) ENHANCE_D->roll_affix(this_object());' in s, f
        assert 'enhance_weapon' not in s, f


def test_storage_chest_keeps_affix():
    s = (MUD / 'custom/home/obj/storage_chest.c').read_text(encoding='utf-8')
    assert 'data["affix"]' in s and 'ENHANCE_D->apply_affix(ob, data["affix"]);' in s


def test_bamboo_fishing_rod_keeps_base_trait():
    s = (MUD / 'custom/weapon/whip/bamboo_fishing_rod.c').read_text(encoding='utf-8')
    assert '"halieutics": 3,' in s and 'ENHANCE_D->roll_affix(this_object());' in s
    d = (MUD / 'adm/daemons/enhanced.c').read_text(encoding='utf-8')
    assert 'affix_base_apply/' in d   # 詞綴加在原本特性上，不會蓋掉
    assert 'bamboo_fishing_rod' in (MUD / 'd/wutang/npc/fisher.c').read_text(encoding='utf-8')


def test_affix_name_uses_weapon_kind_and_one_color():
    src = (MUD / 'adm/daemons/enhanced.c').read_text(encoding='utf-8')
    short = dict(re.findall(r'"(\w+)": "([^"]+)",', src.split('private mapping AFFIX_BASE_SHORT = ([', 1)[1].split(']);', 1)[0]))
    assert short['sword'] == '劍' and short['blade'] == '刀' and short['dagger'] == '匕首' and short['staff'] == '杖'
    # 整把同色：有後綴用後綴的顏色，否則用前綴的顏色。
    assert 'affix_color(suffix ? suffix : prefix)' in src
    assert 'name = affix_short_name(ob, name);' in src
    assert 'set("affix_short_name", "鞭");' in (MUD / 'obj/area/obj/rod.c').read_text(encoding='utf-8')
    assert 'set("affix_short_name", "竿");' in (MUD / 'custom/weapon/whip/bamboo_fishing_rod.c').read_text(encoding='utf-8')


def test_wutang_guard_wields_blade():
    s = (MUD / 'd/wutang/npc/guard.c').read_text(encoding='utf-8')
    assert 'set_skill("blade", 40);' in s
    assert 'carry_object("/obj/area/obj/blade")->wield();' in s
