from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'
C = MUD / 'custom'

WEAPONS = ['sword/charm_sword', 'blade/green_blade', 'sword/jeweled_shortsword', 'sword/ironsword', 'sword/loving_sword',
           'sword/rapid_sword', 'sword/godness_sword', 'sword/royal_sword_of_honor', 'sword/flurry_sword',
           'blade/thunderfurry_blade', 'blade/golden_blade', 'blade/warlord_blade', 'blade/butterfly_kris',
           'dagger/ancient_dagger', 'dagger/coldblood_dagger', 'dagger/dagger_of_fate', 'dagger/dimensional_dagger',
           'dagger/digested_holy_sword', 'needle/tailors_needle', 'staff/flower_cane', 'staff/cane_of_spirit',
           'staff/staff_of_judgement', 'staff/celestial_bull_cane', 'staff/black_spark', 'pike/golden_beast_lance',
           'blunt/black_iron_hammer']
ARMORS = ['cloth/cyan_cloth', 'cloth/umber_robe', 'cloth/worn_robe', 'cloth/suncat_skin', 'armor/ring_mail',
          'armor/wolf_armor', 'armor/battle_armor', 'armor/tiger_armor', 'head/python_headgear', 'head/coral_hairpin',
          'head/hanba_hairpin', 'head/old_silver_hairpin', 'neck/malik_necklace', 'neck/chixiao_necklace',
          'neck/skull_rosary', 'finger/woochan_ring', 'finger/zhuoyu_ring', 'waist/topaz_belt', 'waist/golden_jade_belt',
          'waist/jade_spider_girdle', 'hand/yenhold_gauntlets', 'hand/corrosive_hands', 'hand/silky_gloves',
          'hand/gloves_of_heroism', 'feet/jiaojao_boots', 'feet/runners_boots', 'feet/boots_of_heroism',
          'leg/dingling_legs', 'leg/legs_of_heroism']


def read(p):
    return p.read_text(encoding='utf-8')


def test_files_exist():
    assert len(WEAPONS) == 26 and len(ARMORS) == 29
    for w in WEAPONS:
        s = read(C / 'weapon' / (w + '.c'))
        assert 'init_damage(' in s and 'set("wield_as"' in s and 'apply_weapon/' in s, w
    for a in ARMORS:
        s = read(C / 'armor' / (a + '.c'))
        assert 'set("wear_as"' in s and 'apply_armor/' in s, a


def test_wrapped_blade():
    s = read(C / 'weapon/blade/green_blade.c')
    assert '"纏布刀"' in s and '"玉戒尺"' in s
    assert '你從纏布抽出' not in s and '$N從纏布抽出一把亮晃晃的玉刀，緊握在手上。' in s
    assert '$N將手上的玉刀小心翼翼地收回纏布中。' in s
    assert 'varargs int wield(string as_skill)' in s and 'int unequip()' in s


def test_knock_and_corrupt():
    s = read(C / 'weapon/staff/celestial_bull_cane.c')
    assert 'add_action("do_knock", "knock")' in s and '#define VALUE_PER_SHEET 25' in s
    s = read(C / 'armor/hand/corrosive_hands.c')
    assert 'add_action("do_corrupt", "corrupt")' in s and 'player_corpse' in s
    assert '(me->query_attr("wis") + me->query_attr("cps")) * 3' in s
    assert 'corpse->set ("player_corpse", 1);' in read(MUD / 'adm/daemons/chard.c')


def test_scrolls_and_bag():
    for fn, val in (('blank', 10), ('yang', 50), ('yin', 50), ('nature', 50)):
        s = read(C / 'item/scroll' / (fn + '.c'))
        assert 'inherit COMBINED_ITEM;' in s and f'set("base_value", {val});' in s and 'set("base_weight", 1);' in s
    s = read(C / 'item/dragon_skin_bag.c')
    assert 'set_max_encumbrance(3000000);' in s
    assert 'set_max_encumbrance(30000);' in read(MUD / 'obj/area/obj/bag.c')


def test_identify_labels():
    for p in ('cmds/std/identify.c', 'cmds/wiz/analyze.c'):
        s = read(MUD / p)
        for k in ('"move" : "行動力"', '"fire_damage" : "火焰傷害力"', '"wind_damage" : "風擊傷害力"'):
            assert k in s, (p, k)
