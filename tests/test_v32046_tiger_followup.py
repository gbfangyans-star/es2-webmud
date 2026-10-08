from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
def test_gao_shen_contract():
 s=(MUD/'d/oldpine/npc/kao_shen.c').read_text()
 for x in ['"tiger-force"','"tiger-blade"','"tiger-steps"','"sanmeendo"']:
  assert x in s
 assert 'query_level() < 15' in s and 'query_skill("tiger-force", 1) < 30' in s
def test_enable_contracts():
 # sanmeendo uses the new martial art engine: enable target comes from art_usage
 assert 'art_usage = "blade";' in (MUD/'daemon/skill/sanmeendo.c').read_text()
 assert 'return usage == art_usage;' in (MUD/'std/martial_art.c').read_text()
 assert 'usage=="twohanded blade"' in (MUD/'daemon/skill/tiger-blade.c').read_text()
def test_six_actions_each():
 assert (MUD/'daemon/skill/tiger-blade.c').read_text().count('"action":')==6
 # new sanmeendo design has five moves
 assert (MUD/'daemon/skill/sanmeendo.c').read_text().count('"action":')==5
def test_first_followup_gate():
 s=(MUD/'daemon/skill/tiger-blade.c').read_text()
 assert 'query_skill("tiger-blade",1)<90' in s
 assert 'query("force_ratio")<=70' in s
 assert 'first_follow = strike' in s
def test_second_followup_damage_gate():
 s=(MUD/'daemon/skill/tiger-blade.c').read_text()
 assert 'first_follow<=0' in s
 assert s.count('strike(me,opponent,weapon);')>=2
