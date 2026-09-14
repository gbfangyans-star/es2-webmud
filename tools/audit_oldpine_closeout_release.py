#!/usr/bin/env python3
from pathlib import Path
import hashlib, json, subprocess, sys
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
ROOM=MUD/'custom/oldpine_recovered/room'
NPC=MUD/'custom/oldpine_recovered/npc'
OBJ=NPC/'obj'
checks=[]
def ck(name, ok, detail=''):
    checks.append({'name':name,'ok':bool(ok),'detail':detail})
rooms=sorted(ROOM.glob('*.c'))
ck('41 recovered room LPC files', len(rooms)==41, str(len(rooms)))
# world branch and authority
p8=(MUD/'custom/oldpine/room/path08.c').read_text(errors='ignore')
ck('path08 recovered branch retained', 'oldpine_recovered/room/npath1' in p8)
ck('path08 Gao Shen branch retained', 'path09' in p8)
# explicit blocker isolation
canon=[]
for p in MUD.rglob('*'):
    if p.is_file() and p.suffix in {'.c','.h'} and 'custom/oldpine_recovered' not in p.as_posix():
        try: canon.append(p.read_text(errors='ignore'))
        except: pass
ct='\n'.join(canon)
ck('black_cloth absent from canonical', 'black_cloth' not in ct)
ck('necromancy absent from canonical', 'necromancy' not in ct)
ck('snake_poison absent from canonical', 'snake_poison' not in ct)
pb=(OBJ/'parrybook.c').read_text(errors='ignore')
ck('parrybook legacy contract frozen', all(x in pb for x in ['exp_required":15000','sen_cost":30','difficulty":25','max_skill":50']))
# critical mechanics signatures
critical={
 'dynamic cave reset': ROOM/'cave1.c',
 'dynamic pine maze': ROOM/'pine1.c',
 'cave5 burial': ROOM/'cave5.c',
 'keep ambush': ROOM/'keep2.c',
 'tree vertical route': ROOM/'tree1.c',
 'vine branch': ROOM/'epath2.c',
}
need={
 'dynamic cave reset':['random('], 'dynamic pine maze':['random('],
 'cave5 burial':['bury'], 'keep ambush':['bandit_guard'],
 'tree vertical route':['"up"','"down"'], 'vine branch':['vine']}
for name,p in critical.items():
    t=p.read_text(errors='ignore') if p.exists() else ''
    ck(name, p.exists() and all(s in t for s in need[name]))
# freeze hashes for recovered LPC content
files=sorted([p for p in (MUD/'custom/oldpine_recovered').rglob('*.c')])
hashes={p.relative_to(MUD).as_posix():hashlib.sha256(p.read_bytes()).hexdigest() for p in files}
manifest={'version':'v3.20.45','status':'CONTENT_CLOSED_SOURCE_LEVEL','lpc_files':len(files),'sha256':hashes,
          'compatibility_backlog':['spy:black_cloth','maniac:necromancy','venomsnake:snake_poison','parrybook:F_STUDY_adapter'],
          'live_neolith_acceptance':'pending'}
(ROOT/'reports/oldpine_content_freeze_v32045.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2)+'\n')
passed=sum(x['ok'] for x in checks)
report={'version':'v3.20.45','passed':passed,'total':len(checks),'checks':checks}
(ROOT/'reports/oldpine_closeout_release_audit_v32045.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
for x in checks: print(('PASS' if x['ok'] else 'FAIL'), x['name'], x['detail'])
print(f'{passed}/{len(checks)} PASS')
sys.exit(0 if passed==len(checks) else 1)
