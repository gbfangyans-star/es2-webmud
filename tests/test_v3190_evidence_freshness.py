import json,subprocess,sys,importlib.util
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def loadmod():
 spec=importlib.util.spec_from_file_location('mfp',ROOT/'tools/multiplayer_evidence_fingerprint.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

def test_gate_fingerprints_complete_and_scoped():
 out=loadmod().build();assert out['ok'],out.get('missing')
 assert 'login/tell/save/reconnect' in out['gates']
 assert 'mutual-player-fight' in out['gates']
 assert all(len(x['fingerprint'])==64 for x in out['gates'].values())
 assert all(not f['path'].startswith('web/') for g in out['gates'].values() for f in g['files'])

def test_ledger_has_exact_current_fingerprints_for_passed_baseline():
 out=loadmod().build();ledger=json.loads((ROOT/'MULTIPLAYER_ACCEPTANCE_LEDGER.json').read_text(encoding='utf-8'))
 stored=ledger['evidenceFingerprints']
 for gate in ('transport/session-isolation','login/tell/save/reconnect','same-room/say/team/follow'):
  assert stored[gate]==out['gates'][gate]['fingerprint']

def test_certification_plan_never_promotes_destructive_live():
 r=subprocess.run([sys.executable,str(ROOT/'tools/multiplayer_certification_plan.py')],cwd=ROOT,capture_output=True,text=True)
 assert r.returncode==0,r.stderr
 p=json.loads((ROOT/'reports/multiplayer_certification_plan.json').read_text(encoding='utf-8'))
 death=[x for x in p['nextSteps'] if 'death' in x['gate']][0]
 assert death['mode']=='WITHHELD' and death['risk']=='DESTRUCTIVE'
 assert p['freshness']['login/tell/save/reconnect']['fresh'] is True
 assert p['freshness']['mutual-player-fight']['fresh'] is False
 assert p['freshness']['mutual-player-fight']['implementationUnchanged'] is True

def test_offline_launcher_and_gate_explicitly_refuse_live_claim():
 bat=(ROOT/'CHECK_MULTIPLAYER_OFFLINE.bat').read_text(encoding='utf-8',errors='replace')
 tool=(ROOT/'tools/multiplayer_offline_gate.py').read_text(encoding='utf-8')
 assert 'OFFLINE DEVELOPMENT GATE' in bat
 assert 'liveAcceptanceClaimed' in tool and "'liveAcceptanceClaimed':False" in tool
