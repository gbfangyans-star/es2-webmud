#!/usr/bin/env python3
from pathlib import Path
import json, re, sys
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
checks=[]
def check(name,path,patterns):
    p=M/path
    text=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
    missing=[x for x in patterns if not re.search(x,text,re.S)]
    checks.append({'name':name,'path':str(path),'ok':p.exists() and not missing,'missing':missing})
check('room_say','cmds/std/say.c',[r'all_inventory\(environment\(me\)\)',r'relay_say\(me, arg\)'])
check('private_tell','cmds/std/tell.c',[r'find_player\(target\)',r'tell_object\(obj',r'set_temp\("reply"'])
check('online_users','cmds/usr/who.c',[r'users\(\)',r'objectp\(environment\(\$1\)\)'])
check('clean_quit_save','cmds/usr/quit.c',[r'link_ob->save\(\)',r'me->save\(\)',r'destruct \(me\)'])
check('disconnect_save','obj/user.c',[r'private void net_dead\(\)',r'\bsave\(\);',r'LOGIN_D->net_dead\(this_object\(\)\)'])
check('reconnect','obj/user.c',[r'void reconnect\(\)',r'remove_call_out\("user_dump"\)',r'move\(last_loc\)'])
check('login_netdead','adm/daemons/logind.c',[r'void net_dead\(object ob\)',r'ob->move\("/obj/void"\)'])
out={'ok':all(x['ok'] for x in checks),'scope':'canonical ES2 multiplayer gameplay contracts; static source audit only','checks':checks}
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(0 if out['ok'] else 2)
