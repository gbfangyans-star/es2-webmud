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
