from pathlib import Path
import re,sys
root=Path(__file__).resolve().parents[1]/"source/upstream/mudlib"
r=root/"custom/zhenwu/room"; n=root/"custom/zhenwu/npc"
req=[r/f"yard{i:02d}.c" for i in range(1,15)]+[r/x for x in ("big_tent.c","shed.c","camp.c","gate.c")]+[n/x for x in ("soldier.c","target_stake.c","lu_xinien.c","mee_pei.c")]
miss=[str(x) for x in req if not x.exists()]
assert not miss, miss
assert '"west" : "/custom/zhenwu/room/gate"' in (root/"d/snow/sgate.c").read_text()
text='\n'.join(x.read_text() for x in r.glob('*.c'))
assert text.count('/custom/zhenwu/npc/target_stake')==4
assert '"/custom/zhenwu/npc/soldier" : 2' in (r/'gate.c').read_text()
assert '/custom/zhenwu/npc/lu_xinien' in (r/'yard10.c').read_text()
assert '/custom/zhenwu/npc/mee_pei' in (r/'big_tent.c').read_text()
print('CUSTOM ZHENWU AUDIT: PASS')
