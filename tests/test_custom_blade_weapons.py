from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
BLADE = MUD / 'custom' / 'weapon' / 'blade'


def read(p):
    return p.read_text(encoding='utf-8')


def test_every_blade_answers_to_blade_and_has_damage():
    files = sorted(BLADE.glob('*.c'))
    assert len(files) == 39
    for f in files:
        s = read(f)
        assert re.search(r'set_name\("[^"]*", \(\{ "[^"]+", "blade" \}\)\);', s), f.name
        assert 'init_damage(' in s, f.name
        assert 'set("wield_as"' in s, f.name


def test_weight_caps():
    for f in BLADE.glob('*.c'):
        s = read(f)
        w = int(re.search(r'set_weight\((\d+)\)', s).group(1))
        if '"twohanded blade");' in s and 'init_damage' in s and '"blade");' not in s:
            assert w <= 30000, f.name
        elif f.name != 'black_kris.c':
            assert w <= 12000, f.name
    assert 'set_weight(8500);' in read(BLADE / 'black_kris.c')


def test_unique_blades():
    for name in ['tiger_blade', 'evil_lopsided_blade', 'white_blade', 'cloudy_ring_blade']:
        assert 'inherit F_UNIQUE;' in read(BLADE / f'{name}.c')


def test_left_hand_only_properties():
    for name in ['grin_weapon', 'blue_poison_blade', 'styx_blade']:
        s = read(BLADE / f'{name}.c')
        assert 'set("apply_weapon/secondhand blade"' in s
        assert 'set("apply_weapon/blade"' not in s


def test_blue_poison_blade_venom():
    s = read(BLADE / 'blue_poison_blade.c')
    assert 'void hit_ob(object me, object victim, int damage)' in s
    v = read(MUD / 'daemon' / 'condition' / 'blue_venom.c')
    for x in ['#define DURATION_TICKS  10', '#define BURST_TICKS     2',
              'me->damage_stat("gin", 3, from);', 'me->consume_stat("gin", 5, from);',
              'me->damage_stat("kee", 2, from);', 'me->consume_stat("kee", 4, from);',
              'me->consume_stat("HP", 2, from);', 'data["left"] = DURATION_TICKS;']:
        assert x in v
    assert 'weapon->hit_ob(me, victim, damage);' in read(MUD / 'adm' / 'daemons' / 'combatd.c')
