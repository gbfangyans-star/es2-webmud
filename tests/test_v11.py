import importlib.util
from pathlib import Path
ROOT=Path(__file__).parents[1]
spec=importlib.util.spec_from_file_location('idx',ROOT/'tools/index_es2.py');idx=importlib.util.module_from_spec(spec);spec.loader.exec_module(idx)
src='''int valid_enable(string usage){return usage=="sword" || usage=="parry";} void x(){SKILL_D("sword-art")->attack_using(a,b,c);SKILL_D(skill)->attack_using(a,b,c);}'''
assert idx.parse_valid_enable_literals(src)==['parry','sword']
calls=idx.parse_skill_daemon_calls(src)
assert any(x.get('skill')=='sword-art' and x.get('method')=='attack_using' for x in calls)
assert any(x.get('dynamic') and x.get('expression')=='skill' for x in calls)
w='''void attack_with(object a,object b,string s){} void inflict_damage(){} set("wield_as",({"sword","blade"})); init_damage(1,2,3,4,"sword","blade");'''
wd=idx.parse_weapon_dispatch(w)
assert wd['wield_as']==['sword','blade']
assert wd['damage_skills']==['blade','sword']
print('v1.1 dependency parser tests passed')
