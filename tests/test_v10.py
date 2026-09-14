import importlib.util
from pathlib import Path
ROOT=Path(__file__).parents[1]
spec=importlib.util.spec_from_file_location('idx',ROOT/'tools/index_es2.py');idx=importlib.util.module_from_spec(spec);spec.loader.exec_module(idx)
skill='''int valid_enable(string usage){return usage=="force";} int valid_learn(object me){return 1;} void attack_using(object a, object b, string s){} void exert_function(){}'''
c=idx.parse_skill_contract(skill)
assert 'valid_enable' in c['functions'] and 'attack_using' in c['functions'] and 'exert_function' in c['functions']
eq='''int wear(){return 1;} int remove(){return 1;} int wield(){return 1;} int unwield(){return 1;}'''
h=idx.parse_equipment_hooks(eq)
assert {'wear','remove','wield','unwield'}.issubset(set(h))
d='''int defend(){return 1;} int absorb(){return 0;} int receive_damage(){return 0;}'''
dc=idx.parse_damage_contract(d)
assert {'defend','absorb','receive_damage'}.issubset(set(dc))
acc='''int accept_object(object me, object ob){return 1;} int accept_fight(object me){return 0;}'''
assert set(idx.parse_object_accept_hooks(acc))=={'accept_object','accept_fight'}
print('v1.0 contract parser tests passed')
