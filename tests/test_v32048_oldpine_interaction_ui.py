from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
ROOM=ROOT/'source/upstream/mudlib/custom/oldpine_recovered/room'
WEBHUD=ROOT/'source/upstream/mudlib/cmds/usr/webhud.c'
APP=ROOT/'web/app.js'
HTML=ROOT/'web/index.html'

def text(p): return p.read_text(encoding='utf-8')

def test_recovered_details_use_canonical_room_detail_key():
    for name in ['epath2.c','epath3.c','clearing.c','waterfall.c','riverbank1.c','riverbank2.c','passage.c','path3.c','cave5.c']:
        s=text(ROOM/name)
        assert 'item_desc' not in s
    assert '"footprints"' in text(ROOM/'epath3.c')
    assert '"sign"' in text(ROOM/'clearing.c')
    assert '"vine"' in text(ROOM/'epath2.c')

def test_vine_and_climb_hints_are_visible():
    assert '藤蔓(vine)' in text(ROOM/'epath2.c')
    assert 'climb down' in text(ROOM/'stone.c')
    assert 'climb up/down' in text(ROOM/'cliff1.c')
    assert 'climb up/down' in text(ROOM/'cliff2.c')

def test_hud_emits_room_labels_interactions_and_usable_items_only():
    s=text(WEBHUD)
    assert '@@WEBHUD|ACTBEGIN' in s and '@@WEBHUD|ACTEND' in s
    assert '觀察|look %s' in s and '性命相搏|kill %s' in s and '攻擊|fight %s' in s
    assert '抓住|hold vine' in s and '攀爬|climb pine' in s
    assert 'function_exists("study_ob", ob)' in s
    assert 'action == "none" || command == ""' in s
    assert 'dest_name' in s and '@@WEBHUD|EXIT|%s|%s|%s|%s' in s

def test_browser_has_separate_interaction_panel_and_fast_kick():
    s=text(APP); h=text(HTML)
    assert 'interactionBody' in s and '場景互動' in h
    assert 'HUD_KICK_DELAY_MS = 20' in s
    assert "['eat','drink','study']" in s
    assert 'mergeRuntimeExit(a[2],a[3],a[4],a[5]' in s
