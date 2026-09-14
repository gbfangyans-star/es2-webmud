#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
checks=[]
def chk(name,rel,patterns):
    p=M/rel
    t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
    missing=[pat for pat in patterns if not re.search(pat,t,re.S)]
    checks.append({'name':name,'path':str(rel),'ok':p.exists() and not missing,'missing':missing})

# Login/session identity: same account is explicitly resolved, not duplicated silently.
chk('same_account_takeover','adm/daemons/logind.c',[
    r'find_body\s*\(\s*ob->query\("id"\)\s*\)',
    r'if\s*\(\s*!user->link\(\)\s*\)',
    r'confirm_relogin',
    r'exec\s*\(\s*old_link\s*,\s*user\s*\)',
    r'reconnect\s*\(\s*ob\s*,\s*user\s*\)'])
# Multi-opponent combat is an array, with reciprocal registration by fight/kill commands.
chk('multi_enemy_array','feature/char/attack.c',[
    r'static\s+object\s*\*enemy\s*=\s*\(\{\}\)',
    r'if\s*\(\s*member_array\(ob,\s*enemy\)==-1\s*\)\s*enemy\s*\+=\s*\(\{\s*ob\s*\}\)',
    r'opp\s*=\s*enemy\[random\(sizeof\(enemy\)\)\]'])
chk('reciprocal_fight','cmds/std/fight.c',[r'me->fight_ob\(obj\)',r'obj->fight_ob\(me\)'])
chk('reciprocal_kill','cmds/std/kill.c',[r'me->kill_ob\(obj\)',r'obj->(?:fight_ob|kill_ob)\(me\)'])
# Damage carries attacker identity into the victim's canonical stat machinery.
chk('damage_attacker_identity','feature/char/combat.c',[
    r'receive_damage\s*\(\s*int\s+damage\s*,\s*object\s+from\s*,\s*object\s+attacker\s*\)',
    r'consume_stat\("kee",\s*damage,\s*attacker\)',
    r'consume_stat\("HP",\s*(?:random\(damage\)\+1|damage),\s*attacker\)'])
# Room/private communication contracts and anti-spam/ignore behavior.
chk('room_broadcast','cmds/std/say.c',[r'message\("sound"',r'all_inventory\(environment\(me\)\)',r'relay_say\(me,\s*arg\)'])
chk('private_tell_isolation','cmds/std/tell.c',[
    r'find_player\(target\)',r'tell_object\(obj',r'MIN_TELL_INTERVAL',r'query\("ignore"\)',r'obj->set_temp\("reply"'])
chk('online_enumeration','cmds/usr/who.c',[r'users\(\)',r'objectp\(environment\(\$1\)\)',r'visible\(\$2\)'])
# Save namespace is deterministic per player id and first-letter shard.
chk('per_player_save_namespace','adm/simul_efun/path.c',[
    r'sprintf\("%suser/%c/%s\.o",\s*DATA_DIR,\s*name\[0\],\s*name\)',
    r'sprintf\("%slogin/%c/%s\.o",\s*DATA_DIR,\s*name\[0\],\s*name\)',
    r'sprintf\("%smail/%c/%s\.o",\s*DATA_DIR,\s*name\[0\],\s*name\)'])
chk('clean_quit_save','cmds/usr/quit.c',[r'link_ob->save\(\)',r'me->save\(\)',r'destruct\s*\(me\)'])
chk('disconnect_save','obj/user.c',[r'private\s+void\s+net_dead\(\)',r'\bsave\(\);',r'LOGIN_D->net_dead\(this_object\(\)\)'])
chk('reconnect_location','obj/user.c',[r'void\s+reconnect\(\)',r'move\(last_loc\)'])
# Ground-item contention is serialized through object move; once moved, the old room no longer presents it.
chk('ground_item_atomic_move','cmds/std/get.c',[r'present\(arg,\s*env\)',r'if\s*\(\s*!\s*obj->move\(me\)\s*\)\s*return\s+0'])

out={'ok':all(c['ok'] for c in checks),'scope':'deep canonical ES2 multiplayer contracts; static source audit only','checks':checks}
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(0 if out['ok'] else 2)
