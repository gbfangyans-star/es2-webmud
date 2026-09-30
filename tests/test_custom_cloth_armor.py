from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
CLOTH = MUD / 'custom' / 'armor' / 'cloth'


def read(p):
    return p.read_text(encoding='utf-8')


def test_every_cloth_is_worn_as_cloth():
    files = sorted(CLOTH.glob('*.c'))
    assert len(files) == 63
    for f in files:
        s = read(f)
        assert 'inherit F_CLOTH;' in s, f.name
        assert 'set("wear_as", "cloth");' in s, f.name
        assert 'set("apply_armor/cloth", ([' in s, f.name
        w = int(re.search(r'set_weight\((\d+)\)', s).group(1))
        assert w in (1000, 2000, 4000, 6000), f.name
        v = int(re.search(r'set\("value", (\d+)\)', s).group(1))
        assert 0 < v <= 100000, f.name


def test_dark_cloth_thief_only():
    s = read(CLOTH / 'dark_cloth.c')
    assert 'owner->query_class() != "thief"' in s
    assert 'return ::wear(on_part);' in s


def test_cowhide_vest_renamed():
    assert 'set_name("牛皮背心"' in read(CLOTH / 'cowhide_vest.c')
    s = read(CLOTH / 'leather_vest.c')
    assert 'set_name("皮背心"' in s and '"armor": 2,' in s


def test_skill_names_and_spell_label():
    zh = read(MUD / 'data' / 'chinese.o')
    for k, v in [('great-compassion', '大悲咒'), ('dhyana-essence', '善想禪要'),
                 ('maoshan-illusion', '茅山幻術'), ('taoism-taoshan', '天師道法【桃山密籙】')]:
        assert f'"{k}":"{v}"' in zh
    assert '"spell" : "咒文能力",' in read(MUD / 'cmds' / 'std' / 'identify.c')
    assert '"spell": 25,' in read(CLOTH / 'malik_robe.c')


def test_tight_cloth_follows_source_data():
    s = read(MUD / 'd' / 'lee' / 'obj' / 'tight_cloth.c')
    assert '"defense": 5,' in s and '"armor": 4,' in s
