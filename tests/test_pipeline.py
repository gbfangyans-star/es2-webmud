from pathlib import Path
import importlib.util,tempfile
BASE=Path(__file__).parents[1]
def load(name,file):
    s=importlib.util.spec_from_file_location(name,file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
idx=load('idx',BASE/'tools/index_es2.py')
fixture=BASE/'tests/fixture'; mudlib,meta=idx.verify_repo(fixture,strict_remote=False)
rows=[idx.extract(p,mudlib) for p in mudlib.rglob('*') if p.is_file() and p.suffix in {'.c','.h'}]
room=next(r for r in rows if r['file']=='d/snow/a.c'); npc=next(r for r in rows if r['file']=='d/snow/npc/x.c'); item=next(r for r in rows if r['file']=='d/snow/obj/thing.c')
assert room['exits']['east']=={'target':'b','relative':True}
assert npc['race']=='human' and npc['class']=='commoner' and npc['level']==20
assert npc['attributes']['str']==20 and npc['stat_maximums']['kee']==80
assert npc['skills']==[{'skill':'unarmed','level':12}]
assert npc['skill_maps']==[{'base':'unarmed','mapped_to':'test-art'}]
assert npc['actions']==[{'handler':'do_go','verb':'go'}]
assert npc['merchandise'][0]['target']=='../obj/thing' and npc['merchandise'][0]['stock']==3
assert npc['equipment'][0]['name']=='longsword'
assert item['name']=='測試書' and item['ids']==['test book','book'] and item['weight']==1000
assert item['required_skills']=={'literate':1} and item['study_content']=={'literate':10}
assert 'attack_using' in next(r for r in rows if r['type']=='skill')['functions']
with tempfile.TemporaryDirectory() as d:
    man=idx.write_indexes(rows,Path(d),meta); assert man['counts']['room']==3
print('pipeline tests passed')
