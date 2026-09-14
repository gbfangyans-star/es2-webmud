#!/usr/bin/env python3
"""Non-live multiplayer development gate.

Runs only work that can be proven without the user's Windows Neolith runtime.
It deliberately refuses to claim live gameplay acceptance.
"""
import json,subprocess,sys,time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
VERSION=(ROOT/'VERSION').read_text().strip()

def run(name,cmd):
 t=time.time();p=subprocess.run(cmd,cwd=ROOT);return {'name':name,'status':'PASS' if p.returncode==0 else 'FAIL','exitCode':p.returncode,'seconds':round(time.time()-t,2)}

def main():
 py=sys.executable;node='node';st=[]
 for f in ['audit_multiplayer_gameplay.py','audit_multiplayer_deep.py','audit_multiplayer_v39.py','audit_multiplayer_v310.py','audit_multiplayer_v311.py','audit_multiplayer_v313.py','audit_multiplayer_v314.py','audit_multiplayer_v315.py','audit_multiplayer_v316.py','audit_multiplayer_v317.py','audit_live_test_design.py']:
  st.append(run('static:'+f,[py,str(ROOT/'tools'/f)]))
 st += [
  run('bridge:structural',[node,str(ROOT/'tools/audit_multiplayer_bridge.mjs'),str(ROOT/'server/index.js')]),
  run('bridge:8-session-isolation',[node,str(ROOT/'tests/test_multiplayer_isolation_v34.mjs')]),
  run('bridge:capacity-boundary',[node,str(ROOT/'tests/test_multiplayer_capacity_v35.mjs')]),
  run('bridge:stress-churn',[node,str(ROOT/'tests/test_multiplayer_stress_v35.mjs')]),
  run('bridge:500-session-endurance',[node,str(ROOT/'tests/test_multiplayer_endurance_v317.mjs')]),
  run('bridge:fault-matrix',[node,str(ROOT/'tests/test_multiplayer_fault_matrix_v3191.mjs')]),
  run('evidence:fingerprint',[py,str(ROOT/'tools/multiplayer_evidence_fingerprint.py')]),
  run('evidence:live-carryforward',[py,str(ROOT/'tools/multiplayer_evidence_carryforward.py')]),
  run('evidence:certification-plan',[py,str(ROOT/'tools/multiplayer_certification_plan.py')]),
 ]
 ok=all(x['status']=='PASS' for x in st)
 out={'schema':1,'version':VERSION,'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'scope':'OFFLINE ONLY - no real Neolith or authenticated gameplay','ok':ok,'stages':st,'liveAcceptanceClaimed':False,'note':'PASS means the non-live development gate is clean. It never substitutes for Windows/Neolith live evidence.'}
 p=ROOT/'reports/multiplayer_offline_gate.json';p.parent.mkdir(exist_ok=True);p.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8');print('\nOFFLINE MULTIPLAYER GATE:', 'PASS' if ok else 'FAIL');print('Report:',p);return 0 if ok else 3
if __name__=='__main__':raise SystemExit(main())
