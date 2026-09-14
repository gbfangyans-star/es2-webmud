#!/usr/bin/env python3
from pathlib import Path
import json, hashlib, sys
ROOT=Path(__file__).resolve().parents[1]
CAT=ROOT/'catalog'/'generated'
MUD=ROOT/'source'/'upstream'/'mudlib'
def load(name, default=None):
    try:return json.loads((CAT/name).read_text(encoding='utf-8'))
    except Exception:return default
allrows=load('all.json',[]) or []
bytype={}
manual=[]
for r in allrows:
    t=r.get('type','unknown');bytype[t]=bytype.get(t,0)+1
    if r.get('manual_review'):manual.append({'path':r.get('path'),'file':r.get('file'),'reasons':r.get('manual_review')})
critical=['std/char.c','obj/login.c','obj/user.c','adm/daemons/logind.c','adm/daemons/combatd.c','feature/char/attack.c','feature/char/combat.c','feature/statistic.c']
crit={x:(MUD/x).exists() for x in critical}
ledger={}
try:ledger=json.loads((ROOT/'MULTIPLAYER_ACCEPTANCE_LEDGER.json').read_text(encoding='utf-8'))
except Exception:pass
reports={}
for fn in ['reports/multiplayer_offline_gate.json','reports/multiplayer_fault_matrix_report.json','reports/multiplayer_evidence_carryforward.json','TEST_REPORT.json']:
    p=ROOT/fn
    if p.exists():
        try:
            d=json.loads(p.read_text(encoding='utf-8'));reports[fn]={'present':True,'ok':d.get('ok')}
        except Exception:reports[fn]={'present':True,'ok':None}
    else:reports[fn]={'present':False,'ok':None}
out={
 'version':(ROOT/'VERSION').read_text().strip(),
 'sourceBoundary':'taedlar/es2_mudlib only',
 'canonicalMudlibPresent':MUD.exists(),
 'criticalCore':crit,
 'criticalCoreOK':all(crit.values()),
 'catalog':{'ready':bool(allrows),'entities':len(allrows),'byType':dict(sorted(bytype.items())),'manualReviewCount':len(manual)},
 'multiplayerLedger':{'version':ledger.get('version'),'livePassed':ledger.get('livePassed',[]),'pendingLive':ledger.get('pendingLive',[]),'withheldDestructive':ledger.get('withheldDestructive',[]),'coveredGateFingerprints':ledger.get('coveredGateFingerprints',[])},
 'reports':reports,
 'nextContentPrerequisites':{
   'canonicalSourcePresent':MUD.exists(),
   'catalogReady':bool(allrows),
   'criticalCoreOK':all(crit.values()),
   'manualReviewIsExplicit':True
 },
 'workbench':{'present':(CAT/'content_workbench.json').exists(),'path':'catalog/generated/content_workbench.json'},
 'manualReviewSample':manual[:25]
}
out['ok']=out['canonicalMudlibPresent'] and out['criticalCoreOK'] and out['catalog']['ready'] and out['workbench']['present']
(ROOT/'DEVELOPMENT_READINESS.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out['ok'] else 2)
