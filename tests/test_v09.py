import importlib.util
from pathlib import Path
ROOT=Path(__file__).parents[1]
spec=importlib.util.spec_from_file_location('idx',ROOT/'tools/index_es2.py')
idx=importlib.util.module_from_spec(spec);spec.loader.exec_module(idx)
sample='void update_condition(object me,int d){} void die(){} void receive_damage(){} void x(){ message_vision("x",a,b); }'
assert idx.parse_condition_hooks(sample)==[{'hook':'update_condition'}]
assert 'die' in idx.parse_death_hooks(sample)
assert 'receive_damage' in idx.parse_death_hooks(sample)
assert 'message_vision' in idx.parse_combat_message_traits(sample)
print('v0.9 parser tests passed')
