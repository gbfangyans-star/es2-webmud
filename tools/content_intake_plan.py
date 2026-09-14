#!/usr/bin/env python3
"""Generate a read-only intake plan from canonical catalog/manual-review state."""
from pathlib import Path
import json,time
ROOT=Path(__file__).resolve().parents[1]; CAT=ROOT/'catalog/generated'; REP=ROOT/'reports'
def load(n,d):
 try:return json.loads((CAT/n).read_text(encoding='utf-8'))
 except Exception:return d
rows=load('all.json',[]); wb=load('content_workbench.json',{}); tri=load('triage.json',{})
bytype={}
for x in rows: bytype[x.get('type','unknown')]=bytype.get(x.get('type','unknown'),0)+1
out={'schema':1,'version':(ROOT/'VERSION').read_text().strip(),'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'readOnly':True,'sourceBoundary':'taedlar/es2_mudlib only','canonicalEntities':len(rows),'byType':dict(sorted(bytype.items())),'manualReview':len(wb.get('manualReview',[])),'triageEntries':len(tri.get('ranked',[])),'workflow':['verify source boundary','fingerprint canonical source before work','rebuild catalog/workbench','map supplied material only to source-confirmed entities','preserve unresolved items as manual_review','run catalog diff and canonical source change report','run regression/release gates before packaging'],'prohibitions':['no guessed gameplay','no external gameplay source','no automatic resolution of manual_review','no canonical write without explicit content task and source evidence']}
REP.mkdir(exist_ok=True); (REP/'content_intake_plan.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8'); print(json.dumps({'ok':True,'entities':len(rows),'manualReview':out['manualReview'],'output':'reports/content_intake_plan.json'},ensure_ascii=False))
