from pathlib import Path
import re,sys
root=Path(__file__).resolve().parents[1]
r=root/'source/upstream/mudlib/custom/oldpine_recovered/room'
expected='npath1 npath2 npath3 clearing tree1 tree2 tree3 epath1 epath2 epath3 spath1 spath2 spath3 spath4 passage secrectpath1 path3 stone waterfall riverbank1 riverbank2 lake'.split()
missing=[x for x in expected if not (r/(x+'.c')).exists()]
checks=[]
checks.append(('20plus staged rooms',len(list(r.glob('*.c')))>=20))
checks.append(('expected files',not missing))
checks.append(('npath3-clearing link','__DIR__"clearing"' in (r/'npath3.c').read_text()))
checks.append(('tree layer',all('map/layer","树上' in (r/f'{x}.c').read_text() for x in ['tree1','tree2','tree3'])))
checks.append(('vine split','query_skill("dodge")' in (r/'epath2.c').read_text() and '__DIR__"waterfall"' in (r/'epath2.c').read_text() and '__DIR__"passage"' in (r/'epath2.c').read_text()))
checks.append(('secret chain',all((r/f'{x}.c').exists() for x in ['passage','secrectpath1','path3','stone'])))
checks.append(('gorge chain',all((r/f'{x}.c').exists() for x in ['waterfall','riverbank2','riverbank1','lake'])))
checks.append(('blocked npcs absent',not any('npc/maniac' in p.read_text() or 'npc/spy' in p.read_text() for p in r.glob('*.c'))))
# all literal __DIR__ room refs must resolve, except deliberate next-frontier cave1
broken=[]
for p in r.glob('*.c'):
    for dest in re.findall(r'__DIR__"([A-Za-z0-9_]+)"',p.read_text()):
        if dest=='cave1': continue
        if not (r/(dest+'.c')).exists(): broken.append((p.name,dest))
checks.append(('no accidental broken local refs',not broken))
for name,ok in checks: print(('PASS' if ok else 'FAIL'),name)
if missing: print('missing',missing)
if broken: print('broken',broken)
sys.exit(0 if all(x[1] for x in checks) else 1)
