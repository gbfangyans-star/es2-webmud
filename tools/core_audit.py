#!/usr/bin/env python3
from pathlib import Path
import argparse,json
CRITICAL={
 'connection_login':'/obj/login','player_object':'/obj/user','character':'/std/char',
 'char_attack':'/feature/char/attack','char_combat':'/feature/char/combat','char_skill':'/feature/char/skill',
 'char_condition':'/feature/char/condition','char_statistic':'/feature/statistic',
 'login_daemon':'/adm/daemons/logind','enter_daemon':'/adm/daemons/enterd','combat_daemon':'/adm/daemons/combatd','character_daemon':'/adm/daemons/chard'
}
ap=argparse.ArgumentParser(description='Verify critical ES2 core objects are present in the generated catalog.')
ap.add_argument('catalog');a=ap.parse_args();d=Path(a.catalog)
rows=json.loads((d/'all.json').read_text(encoding='utf-8'));by={r['path']:r for r in rows}
checks={name:{'path':p,'present':p in by,'type':by.get(p,{}).get('type'),'sha256':by.get(p,{}).get('sha256')} for name,p in CRITICAL.items()}
missing=[x for x,v in checks.items() if not v['present']]
report={'ok':not missing,'required':len(CRITICAL),'present':len(CRITICAL)-len(missing),'missing':missing,'checks':checks,'source_policy':'taedlar/es2_mudlib only'}
(d/'core_audit.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(report,ensure_ascii=False,indent=2))
raise SystemExit(0 if not missing else 2)
