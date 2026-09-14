from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def text(p): return (ROOT/p).read_text(encoding='utf-8')

def test_exact_gain_bypasses_legacy_level_bonus_and_has_thresholds():
    s=text('source/upstream/mudlib/feature/char/skill.c')
    assert 'void improve_skill_exact' in s
    assert 'level <= 60' in s and 'base = 100' in s
    assert 'level <= 90' in s and 'base = 125' in s
    assert 'level <= 120' in s and 'base = 150' in s
    assert 'level <= 160' in s and 'base = 175' in s
    assert 'level <= 180' in s and 'base = 200' in s
    assert 'base = 250' in s
    exact=s.split('void improve_skill_exact',1)[1].split('// improve_skill()',1)[0]
    assert 'query_level() / 8' not in exact

def test_d_floor_is_two_and_combat_formulas_present():
    s=text('source/upstream/mudlib/adm/daemons/combatd.c')
    assert 'if( d < 2 ) d = 2;' in s and 'd > 10' in s
    assert '(random(d) + 1) * (random(d) + 1)' in s
    assert '(random(str) + 1) * (random(str) + 1) + random(str)' in s
    assert 'random(me->query_attr("cor"))' in s
    assert 'random(me->query_attr("cps"))' in s

def test_tiger_force_new_milestones_and_private_thresholds():
    s=text('source/upstream/mudlib/daemon/skill/tiger-force.c')
    assert 'level <= 100' in s and 'base = 100' in s
    assert 'level <= 140' in s and 'base = 150' in s
    assert 'level <= 180' in s and 'base = 200' in s
    assert 'lv == 100' in s and '"str"' in s and '+ 1' in s
    assert 'lv == 140' in s and '+ 2' in s
    assert 'lv >= 141' in s

def test_version_bumped():
    assert text('VERSION').strip()>='3.20.59'
