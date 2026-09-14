from pathlib import Path
import json
R=Path(__file__).resolve().parents[1]
md=(R/'reports/oldpine_recovery_round3.md').read_text()
j=json.loads((R/'reports/oldpine_recovery_readiness.json').read_text())
checks={
 'cave5_bury': 'bury skeleton' in md and 'random(kar + 10)' in md,
 'stone_to_cave': 'climb down` -> cave1' in md,
 'tree_layer': 'tree1 <-> tree2 <-> tree3' in md,
 'no_merge': j['playable_merge'] is False,
 'blockers': len(j['blockers'])>=4,
 'gao_shen_unchanged': 'path01..path10 and Gao Shen remain unchanged' in md,
}
for k,v in checks.items(): print(('PASS' if v else 'FAIL'), k)
raise SystemExit(0 if all(checks.values()) else 1)
