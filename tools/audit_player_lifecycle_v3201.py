#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
checks=[]
def ck(name,ok,note=''):
    checks.append({'name':name,'ok':bool(ok),'note':note})
char=(MUD/'std/char.c').read_text(encoding='utf-8',errors='ignore')
chest=(MUD/'custom/home/obj/storage_chest.c').read_text(encoding='utf-8',errors='ignore')
butler=(MUD/'custom/home/npc/butler.c').read_text(encoding='utf-8',errors='ignore')
hall=(MUD/'custom/home/room/home_hall.c').read_text(encoding='utf-8',errors='ignore')
ck('revive_delay_is_20_seconds', bool(re.search(r'call_out\s*\(\s*"revive"\s*,\s*20\s*\)',char)))
ck('death_still_creates_corpse', 'CHAR_D->make_corpse(this_object())' in char)
ck('death_still_announces_dead', 'COMBAT_D->announce(this_object(), "dead")' in char)
ck('home_storage_200_slots', '>= 200' in chest and '/ 200' in chest)
ck('home_storage_saved_to_player', 'custom_home/storage' in chest and 'me->save()' in chest)
ck('home_rooms_saved_to_player', 'custom_home/rooms' in butler and 'me->save()' in butler)
ck('home_room_cap_10', 'rooms >= 10' in butler)
ck('home_room_price_linear_10_gold', 'gold_cost = (rooms + 1) * 10' in butler)
ck('home_owner_bound', 'set_home_owner' in chest and 'set_home_owner' in butler and 'home_owner' in hall)
out={'ok':all(x['ok'] for x in checks),'scope':'v3.20.1 player lifecycle/home persistence static audit','checks':checks}
(ROOT/'reports/player_lifecycle_v3201.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2)); sys.exit(0 if out['ok'] else 2)
