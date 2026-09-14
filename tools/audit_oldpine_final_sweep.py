from pathlib import Path
import re, json, sys
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
R=MUD/'custom/oldpine_recovered/room'; N=MUD/'custom/oldpine_recovered/npc'; O=N/'obj'
expected_rooms={'cave1','cave2','cave3','cave4','cave5','clearing','cliff1','cliff2','cliffdown','cliffside','epath1','epath2','epath3','keep1','keep2','keep3','lake','npath1','npath2','npath3','passage','path3','pine1','pine2','pine3','pine4','pine5','pine6','pine7','riverbank1','riverbank2','secrectpath1','spath1','spath2','spath3','spath4','stone','tree1','tree2','tree3','waterfall'}
rooms={p.stem for p in R.glob('*.c')}
checks=[]
def ck(name,ok,detail=''):
 checks.append((name,bool(ok),detail)); print(('PASS' if ok else 'FAIL'),name,detail)
ck('41/41 recovered rooms',rooms==expected_rooms,f'{len(rooms)}/41')
# local literal refs in recovered files
bad=[]
for p in list(R.glob('*.c'))+list(N.glob('*.c'))+list(O.glob('*.c')):
 s=p.read_text(errors='ignore')
 for rel in re.findall(r'__DIR__\s*"([^"]+)"',s):
  if rel in ('cave','pine'): continue
  # resolve only explicit .c-like local paths, skip runtime strings that are not files
  target=(p.parent/rel)
  if target.suffix=='': target=target.with_suffix('.c')
  if rel.startswith(('room/','npc/')): pass
  if not target.exists() and ('oldpine_recovered' not in rel):
   # __DIR__ relative refs are local and should exist
   bad.append(f'{p.relative_to(MUD)} -> {rel}')
ck('no broken __DIR__ file references',not bad,'; '.join(bad[:8]))
# authoritative branch exists
p08=(MUD/'custom/oldpine/room/path08.c').read_text(errors='ignore')
ck('world branch path08 -> recovered npath1','oldpine_recovered/room/npath1' in p08)
# known content placements
placements={
 'tree2 butterflies':('tree2.c','butterfly'), 'pine1 tall bandit':('pine1.c','tall_bandit'),
 'pine1 fat bandit':('pine1.c','fat_bandit'), 'pine7 wolf dog':('pine7.c','wolf_dog'),
 'keep1 guards':('keep1.c','bandit_guard'), 'keep2 leader':('keep2.c','bandit_leader'),
 'keep3 commander':('keep3.c','bandit_commander'), 'cave5 skeleton':('cave5.c','skeleton')}
for name,(f,tok) in placements.items(): ck(name,tok in (R/f).read_text(errors='ignore'))
# dynamic/special mechanics
ck('cave dynamic reset','random(' in (R/'cave1.c').read_text(errors='ignore'))
ck('pine dynamic reset','random(' in (R/'pine1.c').read_text(errors='ignore'))
keep2=(R/'keep2.c').read_text(errors='ignore')
ck('keep ambush 5 guards',(('i=5' in keep2 and 'while(i--)' in keep2) or 'for(i=0;i<5;i++)' in keep2) and 'kill_ob' in keep2)
ck('keep bamboo callback','pipe_notify' in keep2 and 'pipe_notify' in (O/'bamboo_pipe.c').read_text(errors='ignore'))
c5=(R/'cave5.c').read_text(errors='ignore')
ck('cave5 burial reward','parrybook' in c5 and 'bury' in c5)
# blocker truth against canonical excluding custom
canon=[]
for p in MUD.rglob('*'):
 if p.suffix not in ('.c','.h') or 'custom' in p.parts: continue
 try: canon.append(p.read_text(errors='ignore'))
 except: pass
blob='\n'.join(canon)
for dep in ['black_cloth','snake_poison','necromancy']:
 ck(f'canonical blocker absent: {dep}',dep not in blob)
# parrybook legacy contract preserved but adapter intentionally not falsely enabled
pb=(O/'parrybook.c').read_text(errors='ignore')
ck('parrybook legacy contract preserved',all(x in pb for x in ['exp_required":15000','sen_cost":30','difficulty":25','max_skill":50']))
ck('parrybook modern adapter not falsely claimed','inherit F_STUDY' not in pb)
# inventory
npc_files=sorted(p.stem for p in N.glob('*.c'))
obj_files=sorted(p.stem for p in O.glob('*.c'))
summary={'rooms':len(rooms),'npc_files':npc_files,'object_files':obj_files,'blockers':['spy:black_cloth','maniac:necromancy','venomsnake:snake_poison','parrybook:legacy-study-adapter'],'checks_total':len(checks),'checks_passed':sum(x[1] for x in checks)}
(ROOT/'reports/oldpine_final_sweep_v1.json').write_text(json.dumps(summary,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(summary,ensure_ascii=False))
sys.exit(0 if all(x[1] for x in checks) else 1)
