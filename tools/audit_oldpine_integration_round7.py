from pathlib import Path
import re, sys
root=Path(__file__).resolve().parents[1]
r=root/'source/upstream/mudlib/custom/oldpine_recovered/room'
checks=[]
def ck(name,ok): checks.append((name,bool(ok)))
for n in [f'cave{i}' for i in range(1,6)]+[f'pine{i}' for i in range(1,8)]: ck(f'{n} exists',(r/f'{n}.c').exists())
ck('caves maze metadata',all('set("map/mode","maze")' in (r/f'cave{i}.c').read_text() for i in range(1,5)))
ck('pine maze metadata',all('set("map/mode","maze")' in (r/f'pine{i}.c').read_text() for i in range(1,8)))
ck('cave1 north anchor','"north" : __DIR__"cave2"' in (r/'cave1.c').read_text())
ck('cave2 east anchor','"east" : __DIR__"cave4"' in (r/'cave2.c').read_text())
ck('cave4 west cave5','"west" : __DIR__"cave5"' in (r/'cave4.c').read_text())
ck('cave5 bury','add_action("do_bury","bury")' in (r/'cave5.c').read_text())
ck('parrybook legacy metadata',(root/'source/upstream/mudlib/custom/oldpine_recovered/npc/obj/parrybook.c').exists())
ck('skeleton staged',(root/'source/upstream/mudlib/custom/oldpine_recovered/npc/skeleton.c').exists())
for n,ok in checks: print(('PASS' if ok else 'FAIL'),n)
print(f'{sum(x for _,x in checks)}/{len(checks)} PASS')
sys.exit(0 if all(x for _,x in checks) else 1)
