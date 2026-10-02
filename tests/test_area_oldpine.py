from pathlib import Path
import json
import re

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'
O = MUD / 'd' / 'oldpine'
OPP = {'north': 'south', 'south': 'north', 'east': 'west', 'west': 'east', 'northeast': 'southwest',
       'southwest': 'northeast', 'northwest': 'southeast', 'southeast': 'northwest', 'up': 'down', 'down': 'up'}


def read(p):
    return p.read_text(encoding='utf-8')


def exits(name):
    m = re.search(r'set\("exits", \(\[(.*?)\]\)\);', read(O / (name + '.c')), re.S)
    return dict(re.findall(r'"([a-z]+)" : (?:__DIR__)?"([^"]+)"', m.group(1))) if m else {}


def test_rooms_npcs_and_areas():
    rooms = sorted(p.stem for p in O.glob('*.c'))
    assert len(rooms) == 45
    assert len(list((O / 'npc').glob('*.c'))) == 17
    areas = {}
    for r in rooms:
        s = read(O / (r + '.c'))
        a = re.search(r'set\("map/area", "([^"]+)"\);', s).group(1)
        areas[a] = areas.get(a, 0) + 1
        for npc in re.findall(r'__DIR__"npc/([a-z_]+)"', s):
            assert (O / 'npc' / (npc + '.c')).exists(), (r, npc)
    assert areas == {'老松林': 21, '迷霧森林': 24}


def test_exits_are_two_way():
    # 一般出口都要能走回來；蘆葦叢（迷宮）與出口房、指令出口除外。
    skip = {'reeds', 'reeds_exit', 'wood3', 'ledge'}
    for p in O.glob('*.c'):
        for d, t in exits(p.stem).items():
            if d not in OPP or t.startswith('/') or p.stem in skip:
                continue
            assert exits(t).get(OPP[d]) == p.stem, (p.stem, d, t)


def test_entrance_from_snow_south_gate():
    assert '"southeast" : "/d/oldpine/entrance"' in read(MUD / 'd/snow/sgate.c')
    assert exits('entrance')['northwest'] == '/d/snow/sgate'


def test_reed_maze_sequence_and_layers():
    s = read(O / 'reeds.c')
    assert '({ "north", "north", "east", "west", "north" })' in s
    assert 'set("map/layer", "蘆葦叢");' in s
    assert set(exits('reeds')) == {'north', 'south', 'east', 'west'}
    assert set(exits('reeds_exit')) == {'east'}
    assert exits('wood3')['west'] == 'reeds'


def test_command_exits_and_inn():
    assert 'add_action("do_cave", "cave")' in read(O / 'grass2.c')
    assert 'add_action("do_enter", "enter")' in read(O / 'inn.c') and 'inherit INN;' in read(O / 'inn.c')
    assert 'add_action("do_climb", "climb")' in read(O / 'cave_deep.c')
    assert exits('ledge') == {'down': 'cave_deep'}
    assert exits('kitchen') == {'out': 'inn'}


def test_bandit_bounty_and_aggression():
    for f, n in [('bandit', 15), ('bandit_minion', 5), ('xue_biao', 110)]:
        s = read(O / 'npc' / (f + '.c'))
        assert 'set("bounty", ([ "military service": %d ]));' % n in s
        assert 'kill_ob(ob);' in s
    # 懸賞只由 CHAR_D->make_corpse() 發一次。
    die = read(MUD / 'std/char/npc.c').split('void\ndie()', 1)[1].split('\n}', 1)[0]
    assert 'bounty' not in die and 'gain_score' not in die


def test_beast_strengths():
    want = {'deer': 3, 'rat': 1, 'squirrel': 1, 'wolf': 4, 'wild_bear': 7, 'little_bear': 4, 'big_bear': 5}
    for f, n in want.items():
        assert 'set_strength(this_object(), %d);' % n in read(O / 'npc' / (f + '.c')), f
    assert 'set_strength(this_object(), 4);' in read(MUD / 'd/wutang/npc/boar.c')
    assert 'set_strength(this_object(), 5);' in read(MUD / 'd/wutang/npc/big_boar.c')
    race = read(MUD / 'daemon/race/beast.c')
    assert '"gin":  20, "kee":  30' in race and '"gin": 150, "kee": 250' in race


def test_web_map_has_both_areas():
    g = json.loads(read(ROOT / 'web/world_static_map.json'))
    ids = [n for n in g['nodes'] if n['id'].startswith('/d/oldpine/')]
    assert len(ids) == 45
    assert {n['area'] for n in ids} == {'老松林', '迷霧森林'}
    assert any(e['from'] == '/d/snow/sgate' and e['to'] == '/d/oldpine/entrance' for e in g['edges'])
