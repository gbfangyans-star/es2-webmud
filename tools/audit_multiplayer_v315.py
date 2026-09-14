#!/usr/bin/env python3
from pathlib import Path
import sys
root=Path(sys.argv[1] if len(sys.argv)>1 else Path(__file__).resolve().parents[1])
checks=[]
def ck(name,cond):checks.append((name,bool(cond)))
def text(rel):return (root/rel).read_text(encoding='utf-8',errors='replace')
sv=text('tools/live_multiplayer_resilience.py');srv=text('server/index.js');save=text('source/upstream/mudlib/feature/save.c');usr=text('source/upstream/mudlib/obj/user.c')
ck('resilience uses two distinct existing accounts','ua==ub' in sv)
ck('passwords collected with getpass','getpass.getpass' in sv)
ck('concurrent save wave uses barrier','threading.Barrier(2)' in sv and "c.send('save')" in sv)
ck('save files checked in canonical user shard',"mud/'data/user'/u[0]/(u+'.o')" in sv)
ck('save files checked in canonical login shard',"mud/'data/login'/u[0]/(u+'.o')" in sv)
ck('orphan temp save files checked',"glob(u+'.o.tmp*')" in sv)
ck('new debug log save errors scanned','log_start' in sv and 'debugSaveErrors' in sv)
ck('abrupt reconnect exercised','A.close()' in sv and "'重新連線' in out" in sv)
ck('bidirectional tell exercised',"tell_once(A,B,ub" in sv and "tell_once(B,A,ua" in sv and "sender.send('tell '+target_id" in sv)
ck('bridge remains one TCP per websocket',"net.createConnection({host:MUD_HOST,port:MUD_PORT})" in srv)
ck('bridge capacity remains bounded','MAX_SESSIONS' in srv and 'server at capacity' in srv)
ck('canonical save still calls save_object',('save_object(file)' in save.replace(' ','')))
ck('canonical net_dead still saves player','net_dead()' in usr and 'save();' in usr)
for n,o in checks:print(('[PASS] ' if o else '[FAIL] ')+n)
print(f'{sum(o for _,o in checks)}/{len(checks)} passed')
sys.exit(0 if all(o for _,o in checks) else 3)
