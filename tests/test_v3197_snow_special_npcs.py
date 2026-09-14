import json, subprocess, sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def test_snow_special_npc_audit():
 r=subprocess.run([sys.executable,str(ROOT/'tools/audit_snow_special_npcs.py')],cwd=ROOT,capture_output=True,text=True)
 assert r.returncode==0, r.stdout+r.stderr
 d=json.loads((ROOT/'reports/snow_special_npc_audit.json').read_text(encoding='utf-8'))
 assert d['passed'] is True
 assert d['npcCount']==5
 assert d['canonicalFilesModified'] is False
 assert all(x['roomReferenced'] for x in d['npcs'])
