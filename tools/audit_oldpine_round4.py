#!/usr/bin/env python3
from pathlib import Path
import json,sys
R=Path(__file__).resolve().parents[1]
checks=[]
def ck(name, ok): checks.append((name,bool(ok)))
r=json.loads((R/'reports/oldpine_recovery_readiness.json').read_text())
m=json.loads((R/'reports/oldpine_dependency_matrix_v2.json').read_text())
ck('lineage reconciliation removed', 'later_version_match' not in r['evidence_groups'])
ck('lineage blocker removed', all('later-version' not in x for x in r['blockers']))
ck('separate branch policy', m['integration_policy']['full_oldpine']=='future separate branch')
ck('parrybook recovered but API blocked', any(x['dependency']=='parrybook' and x['status']=='file_recovered_api_blocked' for x in m['dependencies']))
ck('black_cloth remains blocked', any(x['dependency']=='black_cloth' and x['status']=='blocked_missing' for x in m['dependencies']))
ck('necromancy remains blocked', any(x['dependency']=='necromancy' and x['status']=='blocked_missing' for x in m['dependencies']))
ck('skeleton classified item', m['classification_corrections']['skeleton']=='ITEM, not NPC')
ck('canonical F_STUDY exists', (R/'source/upstream/mudlib/feature/study.c').exists())
ck('canonical replica support exists', 'replica_ob' in (R/'source/upstream/mudlib/feature/unique.c').read_text())
for n,o in checks: print(('PASS' if o else 'FAIL'),n)
print(f'{sum(o for _,o in checks)}/{len(checks)} PASS')
sys.exit(0 if all(o for _,o in checks) else 1)
