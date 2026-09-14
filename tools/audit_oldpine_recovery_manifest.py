import json
from pathlib import Path
r=Path(__file__).resolve().parents[1]
d=json.loads((r/'reports/oldpine_source_provenance.json').read_text())
checks={
'canonical boundary recorded': d['current_project_canonical'].endswith('taedlar/es2_mudlib'),
'early archive labeled archaeology': d['status']=='archaeological_version_diff_only',
'41 room files inventoried': d['room_files_confirmed']==41,
'14 NPC code files inventoried': d['npc_code_files_confirmed']==14,
'11 object code files inventoried': d['object_code_files_confirmed']==11,
'no premature merge': d['merge_state']=='not_merged',
}
for k,v in checks.items(): print(('PASS' if v else 'FAIL'),k)
raise SystemExit(0 if all(checks.values()) else 1)
