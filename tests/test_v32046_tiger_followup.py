from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
def test_gao_shen_contract():
 s=(MUD/'custom/oldpine/npc/gao_shen.c').read_text()
 for x in ['"tiger-force"','"tiger-blade"','"tiger-steps"','"sanmeendo"']:
  assert x in s
 assert 'query_level() < 15' in s and 'query_skill("tiger-force", 1) < 30' in s
def test_enable_contracts():
 assert 'usage=="blade"' in (MUD/'daemon/skill/sanmeendo.c').read_text()
 assert 'usage=="twohanded blade"' in (MUD/'daemon/skill/tiger-blade.c').read_text()
def test_six_actions_each():
 for f in ['sanmeendo.c','tiger-blade.c']:
  s=(MUD/'daemon/skill'/f).read_text()
  assert s.count('"action":')==6
def test_first_followup_gate():
 s=(MUD/'daemon/skill/tiger-blade.c').read_text()
 assert 'query_skill("tiger-blade",1)<90' in s
 assert 'query("force_ratio")<=70' in s
 assert 'first_follow = strike' in s
def test_second_followup_damage_gate():
 s=(MUD/'daemon/skill/tiger-blade.c').read_text()
 assert 'first_follow<=0' in s
 assert s.count('strike(me,opponent,weapon);')>=2
