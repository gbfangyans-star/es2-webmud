from pathlib import Path
import json,sys,re
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
app=(ROOT/'web/app.js').read_text(encoding='utf-8')
user=(M/'obj/user.c').read_text(encoding='utf-8')
board=(M/'custom/home/obj/development_board.c').read_text(encoding='utf-8')
bed=(M/'custom/home/obj/bed.c').read_text(encoding='utf-8')
tele=(M/'custom/home/npc/home_teleporter.c').read_text(encoding='utf-8')
item=(M/'std/item.c').read_text(encoding='utf-8')
checks={
 'board_no_missing_object_header':'#include <object.h>' not in board,
 'bed_no_missing_object_header':'#include <object.h>' not in bed,
 'board_item_no_parent_init':'::init();' not in board,
 'bed_item_no_parent_init':'::init();' not in bed,
 'item_base_has_no_init':'void init' not in item,
 'hud_not_rate_limited':'if (str != "webhud")' in user,
 'hud_poll_reduced':'const HUD_POLL_MS = 800;' in app,
 'hud_yields_to_player':'Date.now()-lastUserCommandAt<HUD_USER_GRACE_MS' in app,
 'hud_kick_debounced':'kickHudAfterServerText' in app and 'clearTimeout(hudKickTimer)' in app,
 'wizard_home_not_shadowed':'query_verb() == "home" && wizardp(me)' in tele,
}
fail=[k for k,v in checks.items() if not v]
out={'version':(ROOT/'VERSION').read_text().strip(),'checks':checks,'failures':fail,'passed':not fail}
(ROOT/'reports/home_runtime_compat_audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2));sys.exit(0 if not fail else 1)
