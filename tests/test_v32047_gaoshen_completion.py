from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / "source" / "upstream" / "mudlib"


def text(rel):
    return (MUD / rel).read_text(encoding="utf-8")


def test_tiger_steps_has_six_attempt_narratives_and_neutral_dodge_formula():
    s = text("daemon/skill/tiger-steps.c")
    assert s.count('"$N') == 6
    assert 'return me->query_skill("dodge")' in s
    assert 'valid_enable(string usage)' in s and 'usage == "dodge"' in s
    assert 'message_vision' in s
    assert 'apply/dodge' not in s
    assert 'random(100)' not in s


def test_tiger_force_user_growth_table_and_powerup_formula():
    s = text("daemon/skill/tiger-force.c")
    assert 'lv >= 161' in s
    assert 'advance_stat("gin", 1)' in s and 'advance_stat("kee", 1)' in s
    assert 'lv >= 141' in s
    assert 'advance_stat("gin", 3)' in s and 'advance_stat("kee", 4)' in s
    assert 'advance_stat("gin", 2)' in s and 'advance_stat("kee", 2)' in s
    assert 'lv == 100' in s and 'query_attr("str", 1) + 1' in s and 'query_attr("cor", 1) + 1' in s
    assert 'lv == 140' in s and 'query_attr("cor", 1) + 2' in s
    assert 'damage_bonus = sk / 4' in s
    assert 'attack_bonus = sk / 3' in s
    assert 'duration = sk * 3 / 2' in s
    assert 'sk < 100' in s
    assert 'consume_stat("kee", 2)' in s and 'damage_stat("kee", 1)' in s
    assert 'consume_stat("gin", 3)' in s and 'damage_stat("gin", 1)' in s


def test_gao_shen_tiger_force_completes_at_twenty_and_grants_root_bonus():
    # 高慎只傳授入門點數；累積到 20 級門檻後下 gain 才練成 20 級並給根骨。
    g = text("d/oldpine/npc/kao_shen.c")
    assert 'me->set_skill(skill, 20)' not in g
    assert 'me->improve_skill_exact(skill,' in g
    s = text("daemon/skill/tiger-force.c")
    assert 'int query_entry_level() { return 20; }' in s
    assert 'void skill_completed(object me, string sk)' in s
    assert 'query_attr("con", 1) + 1' in s
    assert 'me->set("tiger_force/growth_level", 20)' in s


def test_tiger_blade_followup_and_moves_remain_present():
    # tiger-blade rewritten on the new martial art engine: eight moves from the
    # Han Xiao battle record; the 2010 follow-up gate is unchanged.
    s = text("daemon/skill/tiger-blade.c")
    assert s.count('"action":') == 8
    assert 'me->query_skill("tiger-blade", 1) < 90 || ratio <= 70' in s
    assert 'first_follow = strike' in s
    assert 'if( first_follow <= 0' in s
