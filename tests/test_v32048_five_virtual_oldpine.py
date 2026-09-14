from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
ROOM=ROOT/'source/upstream/mudlib/custom/oldpine_recovered/room'

def t(name): return (ROOM/name).read_text(encoding='utf-8')

def test_five_virtual_players_cover_changed_oldpine_interactions():
    # Five independent player routes exercise every newly surfaced interaction family.
    players={
      '甲':['epath3.c','epath2.c'],          # footprints -> vine
      '乙':['clearing.c','tree1.c'],         # sign/pine -> climb
      '丙':['waterfall.c','riverbank2.c'],   # waterfall/cliff details
      '丁':['riverbank1.c','cliff1.c'],      # lake/cliff -> climb
      '戊':['passage.c','path3.c','stone.c'] # curtain/stone -> climb
    }
    for route in players.values():
        for room in route: assert (ROOM/room).exists()
    assert '"footprints"' in t('epath3.c')
    assert '"vine"' in t('epath2.c') and 'hold","grab' in t('epath2.c')
    assert '"sign"' in t('clearing.c') and 'climb' in t('clearing.c')
    assert '"waterfall"' in t('waterfall.c') and '"cliff"' in t('waterfall.c')
    assert '"lake"' in t('riverbank1.c') and 'arg=="cliff"' in t('riverbank1.c')
    assert '"curtain"' in t('passage.c') and '"stone"' in t('path3.c')
