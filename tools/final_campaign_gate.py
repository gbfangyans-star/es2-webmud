#!/usr/bin/env python3
from pathlib import Path
import argparse,subprocess,sys,json
ap=argparse.ArgumentParser()
ap.add_argument('--campaign',required=True)
ap.add_argument('--release',required=True)
ap.add_argument('--runtime-bundle',required=True)
ap.add_argument('--session-package',required=True)
ap.add_argument('--multiplayer',required=True)
ap.add_argument('--out',required=True)
a=ap.parse_args()
here=Path(__file__).resolve().parent

def run(cmd):
    p=subprocess.run(cmd,capture_output=True,text=True)
    try:payload=json.loads(p.stdout) if p.stdout.strip() else {}
    except:payload={'stdout':p.stdout,'stderr':p.stderr}
    return {'ok':p.returncode==0,'code':p.returncode,'result':payload}

steps={}
steps['provenance']=run([
    sys.executable,str(here/'validate_campaign_provenance.py'),
    '--campaign',a.campaign,'--release',a.release,'--runtime-bundle',a.runtime_bundle,
    '--session-package',a.session_package,'--multiplayer',a.multiplayer
])
try:
    release=json.loads(Path(a.release).read_text(encoding='utf-8'))
    steps['release']={'ok':bool(release.get('ok')),'result':release}
except Exception as e:
    steps['release']={'ok':False,'result':{'error':str(e)}}
steps['runtime_evidence']=run([sys.executable,str(here/'validate_runtime_evidence.py'),a.runtime_bundle])
steps['session_package']=run(['node',str(here/'validate_session_package.mjs'),a.session_package])
steps['multiplayer']=run(['node',str(here/'validate_multiplayer_plan.mjs'),'--plan',a.multiplayer])
if steps['session_package']['ok'] and not steps['session_package']['result'].get('acceptanceComplete'):
    steps['session_package']['ok']=False
    steps['session_package']['result']['gate']='acceptance_incomplete'
complete=all(x['ok'] for x in steps.values())
out={
 'format':'es2-final-campaign-gate-v2',
 'ok':complete,
 'campaignId':steps['provenance']['result'].get('campaignId'),
 'steps':steps,
 'note':'PASS requires exact provenance binding plus release, runtime evidence, complete session acceptance, and evidence-backed multiplayer validation.'
}
Path(a.out).write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'ok':out['ok'],'campaignId':out.get('campaignId'),'failed':[k for k,v in steps.items() if not v['ok']],'out':a.out},ensure_ascii=False,indent=2))
raise SystemExit(0 if out['ok'] else 2)
