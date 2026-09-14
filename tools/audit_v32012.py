from pathlib import Path
import json,sys
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
read=lambda p:(M/p).read_text(encoding='utf-8')
app=(ROOT/'web/app.js').read_text(encoding='utf-8')
channel=read('adm/daemons/channeld.c')
woochan=read('daemon/race/woochan.c')
stat=read('feature/statistic.c')
score=read('cmds/usr/score.c')
checks={
 'chat_level_gate_removed_only_for_chat':'me->query("level") < 2 && verb != "chat"' in channel,
 'woochan_food_zero_zero':all(x in woochan for x in ['set_stat_current("food", 0)','set_stat_effective("food", 0)','set_stat_maximum("food", 0)']),
 'woochan_hunger_does_not_block_heal':'me->query_race() != "woochan"' in stat and 'query_stat("food") < 1' in stat,
 'score_25_cells':'val * 25 / max' in score and 'eff * 25 / max - n_filled' in score and 'val * 50 / max' not in score,
 'hud_one_second_poll':'const HUD_POLL_MS = 1000;' in app,
 'hud_no_prompt_dependency':'function hudPollReady()' in app and "if(!p.endsWith('>'))return false" not in app,
 'hud_immediate_after_game_text':"setTimeout(pollHud,80)" in app,
}
fail=[k for k,v in checks.items() if not v]
out={'version':(ROOT/'VERSION').read_text().strip(),'checks':checks,'failures':fail,'passed':not fail}
(ROOT/'reports/v32012_audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(1 if fail else 0)
