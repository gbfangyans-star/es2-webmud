from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SKILL = ROOT / 'source/upstream/mudlib/feature/char/skill.c'

def text():
    return SKILL.read_text(encoding='utf-8')

def threshold(level):
    if level <= 60: base = 100
    elif level <= 90: base = 125
    elif level <= 120: base = 150
    elif level <= 160: base = 175
    elif level <= 180: base = 200
    else: base = 250
    return level * level * base

def test_old_neolith_forward_prototype_is_preserved():
    s = text()
    assert 'varargs int query_attr(string attr, int raw);' in s

def test_common_threshold_breakpoints():
    assert threshold(1) == 100
    assert threshold(60) == 360000
    assert threshold(61) == 465125
    assert threshold(90) == 1012500
    assert threshold(91) == 1242150
    assert threshold(120) == 2160000
    assert threshold(121) == 2562175
    assert threshold(160) == 4480000
    assert threshold(161) == 5184200
    assert threshold(180) == 6480000
    assert threshold(181) == 8190250
    assert threshold(200) == 10000000

def test_restored_skills_and_caps_are_explicit_without_member_array_literal():
    s = text()
    for name in ('unarmed','parry','dodge','blade','twohanded blade','secondhand blade','force','tiger-steps','tiger-blade','sanmeendo'):
        assert f'if( skill == "{name}" ) return 1;' in s
    assert 'if( skill == "tiger-steps" ) return 120;' in s
    assert 'if( skill == "tiger-blade" || skill == "sanmeendo" ) return 140;' in s
    assert 'member_array(skill' not in s

def test_progression_is_called_after_daemon_hook_and_uses_conservative_call_other():
    s = text()
    exact = s.split('void improve_skill_exact',1)[1].split('int restored_force_tick_exp',1)[0]
    assert 'function_exists("skill_improved", daemon)' in exact
    assert 'call_other(daemon, "skill_improved", this_object(), skill);' in exact
    assert 'daemon->skill_improved' not in exact
    assert exact.index('call_other(daemon, "skill_improved"') < exact.index('apply_restored_skill_progression(skill);')

def test_version():
    assert (ROOT/'VERSION').read_text().strip() == '3.20.76'
