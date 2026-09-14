#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]; M=ROOT/'source/upstream/mudlib'; checks=[]
def chk(name,rel,patterns):
 p=M/rel; t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''; miss=[x for x in patterns if not re.search(x,t,re.S)]; checks.append({'name':name,'path':rel,'ok':p.exists() and not miss,'missing':miss})
chk('player_to_player_give','cmds/std/give.c',[r'present\(target,\s*environment\(me\)\)',r'if\s*\(\s*!item->move\(who\)\s*\)\s*return\s+0',r'message_vision\("\$N交給\$n'])
chk('give_rejects_self','cmds/std/give.c',[r'if\(who==me\)\s*return\s+notify_fail'])
chk('give_rejects_nodrop','cmds/std/give.c',[r'item->query\("no_drop"\)'])
chk('linkdead_stops_combat','obj/user.c',[r'private\s+void\s+net_dead\(\).*?remove_all_enemy\(\)',r'set_temp\("last_location"',r'call_out\("user_dump",\s*NET_DEAD_TIMEOUT'])
chk('linkdead_moves_to_void','adm/daemons/logind.c',[r'void\s+net_dead\(object ob\).*?ob->move\("/obj/void"\)'])
chk('reconnect_restores_room','obj/user.c',[r'void\s+reconnect\(\).*?remove_call_out\("user_dump"\).*?move\(last_loc\)'])
chk('combat_drops_remote_targets','feature/char/attack.c',[r'clean_up_enemy\s*\(\).*?environment\(\$1\)==environment\(\)'])
chk('drop_moves_single_object','cmds/std/drop.c',[r'if\s*\(obj->move\(environment\(me\)\)\)'])
chk('get_moves_single_object','cmds/std/get.c',[r'if\s*\(\s*!\s*obj->move\(me\)\s*\)\s*return\s+0'])
out={'ok':all(x['ok'] for x in checks),'scope':'v3.9 canonical multiplayer interaction/lifecycle static audit','checks':checks}; print(json.dumps(out,ensure_ascii=False,indent=2)); sys.exit(0 if out['ok'] else 2)
