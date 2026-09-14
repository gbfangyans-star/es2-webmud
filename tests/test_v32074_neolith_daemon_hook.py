from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SKILL = ROOT / "source/upstream/mudlib/feature/char/skill.c"

def src():
    return SKILL.read_text(encoding="utf-8")

def test_old_neolith_query_attr_prototype_is_preserved():
    s = src()
    assert "varargs int query_attr(string attr, int raw);" in s

def test_round2_uses_object_guard_and_call_other():
    s = src()
    assert "object daemon;" in s
    assert "daemon = SKILL_D(skill);" in s
    assert "if( objectp(daemon) )" in s
    assert 'function_exists("skill_improved", daemon)' in s
    assert 'call_other(daemon, "skill_improved", this_object(), skill);' in s

def test_no_object_string_comparison_regression():
    s = src()
    assert "daemon != DAEMON_D" not in s
    assert "daemon == DAEMON_D" not in s
