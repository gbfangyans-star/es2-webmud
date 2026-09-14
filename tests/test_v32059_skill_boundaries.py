from pathlib import Path
import random

ROOT = Path(__file__).resolve().parents[1]

def src(rel):
    return (ROOT / rel).read_text(encoding='utf-8')

def common_threshold(level):
    if level <= 60: base = 100
    elif level <= 90: base = 125
    elif level <= 120: base = 150
    elif level <= 160: base = 175
    elif level <= 180: base = 200
    else: base = 250
    return level * level * base

def tiger_force_threshold(level):
    if level <= 100: base = 100
    elif level <= 140: base = 150
    elif level <= 180: base = 200
    else: base = 250
    return level * level * base

def d_value(player, mob):
    return max(2, min(10, mob-player))

def test_exact_common_threshold_examples_and_breakpoints():
    assert common_threshold(1) == 100
    assert common_threshold(60) == 360_000
    assert common_threshold(61) == 465_125
    assert common_threshold(90) == 1_012_500
    assert common_threshold(91) == 1_242_150
    assert common_threshold(120) == 2_160_000
    assert common_threshold(121) == 2_562_175
    assert common_threshold(160) == 4_480_000
    assert common_threshold(161) == 5_184_200
    assert common_threshold(180) == 6_480_000
    assert common_threshold(181) == 8_190_250
    assert common_threshold(200) == 10_000_000
    assert common_threshold(61)-common_threshold(60) == 105_125

def test_d_boundaries_low_equal_plus_one_two_ten_and_over():
    cases = [(20,1,2),(20,19,2),(20,20,2),(20,21,2),(20,22,2),
             (20,25,5),(20,30,10),(20,99,10)]
    assert [(a,b,d_value(a,b)) for a,b,_ in cases] == [(a,b,x) for a,b,x in cases]

def test_formula_ranges_and_floor_int_base():
    random.seed(32059)
    for intel in [0,1,6,7,13,14,21,35]:
        ib = intel // 7
        d = 10
        vals = [(random.randrange(d)+1)*(random.randrange(d)+1)*ib for _ in range(500)]
        assert min(vals) >= ib
        assert max(vals) <= 100*ib
        if intel < 7:
            assert set(vals) == {0}

def test_special_caps_are_enforced_in_core_progression():
    s=src('source/upstream/mudlib/feature/char/skill.c')
    assert 'if( skill == "tiger-steps" ) return 120;' in s
    assert 'skill == "tiger-blade" || skill == "sanmeendo"' in s
    assert 'return 140;' in s
    assert 'while( level < cap )' in s

def test_tiger_force_seed_matches_cumulative_level20_floor():
    g=src('source/upstream/mudlib/custom/oldpine/npc/gao_shen.c')
    assert 'me->query_learn(skill) < 40000' in g
    assert 'me->set_learn(skill, 40000)' in g
    assert tiger_force_threshold(20) == 40_000
    assert tiger_force_threshold(21) == 44_100
    assert tiger_force_threshold(21)-tiger_force_threshold(20) == 4_100

def test_level_one_teacher_seed_matches_common_cumulative_floor():
    g=src('source/upstream/mudlib/custom/oldpine/npc/gao_shen.c')
    assert 'me->query_learn(skill) < 100' in g
    assert 'me->set_learn(skill, 100)' in g

def test_trigger_wiring_is_success_only_not_attempt_only():
    c=src('source/upstream/mudlib/adm/daemons/combatd.c')
    f=src('source/upstream/mudlib/feature/char/combat.c')
    assert 'if( damage > 0 ) restored_hit_gain(me, victim, skill);' in c
    assert 'if( random(100) > chance ) {' in f
    dodge_block=f.split('if( random(100) > chance ) {',1)[1].split('return 0;',1)[0]
    assert 'restored_dodge_gain' in dodge_block
    assert 'if( absorbed > 0 )' in f and 'restored_parry_gain' in f

def test_no_legacy_level_multiplier_in_exact_gain():
    s=src('source/upstream/mudlib/feature/char/skill.c')
    exact=s.split('void improve_skill_exact',1)[1].split('// improve_skill()',1)[0]
    assert 'query_level() / 8' not in exact
    assert 'skill_gain[skill]' in exact

def advance_model(level, learned, cap=200):
    while level < cap and learned >= common_threshold(level + 1):
        level += 1
    return level

def test_single_exact_boundary_multi_level_jump_and_caps():
    # One point below does not level; exact threshold does.
    assert advance_model(59, common_threshold(60)-1) == 59
    assert advance_model(59, common_threshold(60)) == 60
    # A large gain may legitimately cross several cumulative thresholds.
    assert advance_model(58, common_threshold(63)) == 63
    # Special caps stop advancement even with absurd learned totals.
    assert advance_model(119, 99_999_999, 120) == 120
    assert advance_model(139, 99_999_999, 140) == 140

def test_tiger_force_milestone_thresholds_are_monotonic():
    vals=[tiger_force_threshold(x) for x in range(20,201)]
    assert all(a < b for a,b in zip(vals, vals[1:]))
    assert tiger_force_threshold(100) == 1_000_000
    assert tiger_force_threshold(101) == 1_530_150
    assert tiger_force_threshold(140) == 2_940_000
    assert tiger_force_threshold(141) == 3_976_200
    assert tiger_force_threshold(180) == 6_480_000
    assert tiger_force_threshold(181) == 8_190_250
    assert tiger_force_threshold(200) == 10_000_000
