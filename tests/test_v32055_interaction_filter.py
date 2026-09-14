from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
HUD=(ROOT/'source/upstream/mudlib/cmds/usr/webhud.c').read_text()
INN=(ROOT/'source/upstream/mudlib/d/snow/inn_hall.c').read_text()

def test_no_generic_detail_enumeration():
    assert 'details = room->query("detail")' not in HUD
    assert 'foreach (id, desc in details)' not in HUD

def test_action_registry_supported():
    assert 'room->query("web_actions")' in HUD
    assert 'ob->query("web_actions")' in HUD

def test_no_combat_buttons_in_safe_room():
    assert 'if (!room->query("no_fight"))' in HUD
    assert 'set ("no_fight",1);' in INN

def test_vendor_and_home_actions_are_real_commands():
    assert 'function_exists("do_vendor_list", ob)' in HUD
    assert '|商品|list %s' in HUD
    assert '|傳送至家園|home' in HUD

def test_oldpine_real_actions_preserved():
    for cmd in ['look vine','hold vine','look footprints','climb pine','climb up','climb down','climb cliff']:
        assert cmd in HUD
