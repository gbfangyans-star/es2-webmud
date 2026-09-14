#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]; M=ROOT/'source/upstream/mudlib'; checks=[]
def chk(name,rel,patterns):
 p=M/rel; t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''; miss=[x for x in patterns if not re.search(x,t,re.S)]; checks.append({'name':name,'path':rel,'ok':p.exists() and not miss,'missing':miss})
chk('follow_rejects_linkdead_players','cmds/std/follow.c',[r'userp\(ob\) && !interactive\(ob\)',r'me->set_leader\(ob\)'])
chk('movement_notifies_room_and_invokes_followers','cmds/std/go.c',[r'message\(\s*"vision".*?old_env',r'me->move\(obj\)',r'all_inventory\(old_env\)->follow_me\(me, dir\)'])
chk('follower_uses_canonical_go_command','feature/char/team.c',[r'ob != leader',r'command\("go " \+ dir\)',r'clean_up_enemy\(\)'])
chk('team_and_follow_are_independent','cmds/std/team.c',[r'team 跟 follow 是獨立的'])
chk('guard_requires_online_room_player','cmds/std/guard.c',[r'present\(arg, environment\(me\)\)',r'!userp\(ob\)',r'me->guard_ob\(ob\)'])
chk('guard_joins_only_when_present','feature/char/attack.c',[r'environment\(\$1\)==environment\(\)',r'guard->activate_guard\(this_object\(\)\)'])
chk('say_is_room_scoped','cmds/std/say.c',[r'message\("sound".*?environment\(me\), me\)',r'all_inventory\(environment\(me\)\) - \(\{ me \}\)',r'relay_say\(me, arg\)'])
chk('tell_is_direct_online_player_route','cmds/std/tell.c',[r'obj = find_player\(target\)',r'if\(!interactive\(obj\)\)',r'tell_object\(obj, sprintf'])
chk('tell_has_sender_rate_limit','cmds/std/tell.c',[r'MIN_TELL_INTERVAL\s+3',r'last_tell_time'])
chk('pvp_rejects_linkdead_fight','cmds/std/fight.c',[r'userp\(obj\) && !interactive\(obj\)'])
chk('pvp_rejects_linkdead_kill','cmds/std/kill.c',[r'userp\(obj\) && !interactive\(obj\)'])
chk('team_handshake_is_same_room','cmds/std/team.c',[r'present\(arg, environment\(me\)\)',r'pending/team'])
chk('team_chat_is_scoped_to_team_array','cmds/std/team.c',[r'message\("team".*?t\)'])
out={'ok':all(x['ok'] for x in checks),'scope':'v3.13 canonical live-multiplayer movement/room/team/guard audit','checks':checks}
print(json.dumps(out,ensure_ascii=False,indent=2)); sys.exit(0 if out['ok'] else 2)
