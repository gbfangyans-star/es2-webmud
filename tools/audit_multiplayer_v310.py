#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]; M=ROOT/'source/upstream/mudlib'; checks=[]
def chk(name,rel,patterns):
 p=M/rel; t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''; miss=[x for x in patterns if not re.search(x,t,re.S)]; checks.append({'name':name,'path':rel,'ok':p.exists() and not miss,'missing':miss})
chk('pvp_fight_requires_mutual_consent','cmds/std/fight.c',[r'userp\(obj\).*?pending/fight',r'obj->query_temp\("pending/fight"\)==me',r'me->fight_ob\(obj\)',r'obj->fight_ob\(me\)'])
chk('pvp_kill_warns_target','cmds/std/kill.c',[r'if\( userp\(obj\) \)',r'obj->fight_ob\(me\)',r'請你也對這個人下一次 kill 指令'])
chk('offline_players_not_attackable_fight','cmds/std/fight.c',[r'userp\(obj\) && !interactive\(obj\)'])
chk('offline_players_not_attackable_kill','cmds/std/kill.c',[r'userp\(obj\) && !interactive\(obj\)'])
chk('multi_enemy_state_is_per_character','feature/char/attack.c',[r'static object \*enemy = \(\{\}\)',r'query_enemy\(\).*?return enemy',r'if\( member_array\(ob, enemy\)==-1 \)\s*enemy \+= \(\{ ob \}\)'])
chk('combat_targets_same_room_only','feature/char/attack.c',[r'environment\(ob\) != environment\(\)',r'environment\(\$1\)==environment\(\)'])
chk('guard_can_join_same_room_fight','feature/char/attack.c',[r'wake_guard',r'environment\(\$1\)==environment\(\)',r'guard->activate_guard\(this_object\(\)\)'])
chk('team_requires_two_party_handshake','cmds/std/team.c',[r'pending/team',r'如果你願意加入.*team with',r'add_team_member'])
chk('team_chat_is_team_scoped','cmds/std/team.c',[r'message\("team".*?t\)'])
chk('team_members_share_team_array','feature/char/team.c',[r'foreach\(member in team\) member->set_team\(team\)'])
chk('team_quit_cleanup','cmds/usr/quit.c',[r'query_team\(\)',r'dismiss_team\(\)'])
chk('enemy_cleanup_after_room_change','feature/char/attack.c',[r'clean_up_enemy\s*\(\).*?environment\(\$1\)==environment\(\)'])
out={'ok':all(x['ok'] for x in checks),'scope':'v3.10 canonical PvP/team/shared-combat static audit','checks':checks}; print(json.dumps(out,ensure_ascii=False,indent=2)); sys.exit(0 if out['ok'] else 2)
