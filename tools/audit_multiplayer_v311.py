#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]; M=ROOT/'source/upstream/mudlib'; checks=[]
def chk(name,rel,patterns):
 p=M/rel; t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''; miss=[x for x in patterns if not re.search(x,t,re.S)]; checks.append({'name':name,'path':rel,'ok':p.exists() and not miss,'missing':miss})
chk('death_clears_combat_guard_team','std/char.c',[r'void\s*\n?die\(\).*?remove_all_killer\(\).*?guard_ob\(0\).*?charge_ob\(0\).*?dismiss_team\(\)'])
chk('death_announced_and_corpse_created','std/char.c',[r'COMBAT_D->announce\(this_object\(\), "dead"\)',r'CHAR_D->make_corpse\(this_object\(\)\)'])
chk('corpse_receives_victim_inventory','adm/daemons/chard.c',[r'foreach \(inv in all_inventory\(victim\)\)\s*inv->move \(corpse\)'])
chk('corpse_decay_lifecycle','obj/corpse.c',[r'case 1:.*?腐爛',r'case 2:.*?骸骨',r'case 3:.*?destruct\(this_object\(\)\)'])
chk('killer_attribution_uses_last_damage','adm/daemons/chard.c',[r'if \(!killer\)\s*killer = victim->last_damage_giver\(\)'])
chk('pk_penalty_and_record_are_per_killer','adm/daemons/chard.c',[r'userp \(victim\) && userp \(killer\)',r'killer->gain_score \("mortal sin"',r'killer->set\("last_pk_time", time\(\)\)',r'killer->add\("pk_record", 1\)'])
chk('npc_kill_bounty_goes_to_damage_giver','std/char/npc.c',[r'last_damage_giver\(\)',r'ob->gain_score\(score, amount\)'])
chk('corpse_look_exposes_remains','cmds/std/look.c',[r'obj->is_corpse\(\)',r'遺物'])
chk('ghost_cannot_loot','cmds/std/get.c',[r'life_form"\) == "ghost"',r'快去找城隍復活'])
chk('living_death_transitions_to_ghost','std/race/humanoid.c',[r'if\( flag\["HP"\] \).*?ob->die\(\).*?case "living":.*?CHAR_D->make_ghost\(ob\)'])
chk('ghost_death_transitions_to_mist','std/race/humanoid.c',[r'case "ghost":.*?CHAR_D->make_mist\(ob\)'])
chk('temple_revives_ghost_via_canonical_daemon','std/room/temple.c',[r'query\("life_form"\) != "ghost"',r'CHAR_D->make_living \(this_player\(\)\)'])
out={'ok':all(x['ok'] for x in checks),'scope':'v3.11 canonical multiplayer death/corpse/PK/revival static audit','checks':checks}; print(json.dumps(out,ensure_ascii=False,indent=2)); sys.exit(0 if out['ok'] else 2)
