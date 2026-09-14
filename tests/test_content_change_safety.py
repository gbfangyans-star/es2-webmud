from pathlib import Path
import subprocess,sys,json
ROOT=Path(__file__).resolve().parents[1]
def test_impact_is_read_only_and_clean():
 r=subprocess.run([sys.executable,str(ROOT/'tools/content_change_impact.py')],cwd=ROOT,text=True,capture_output=True)
 assert r.returncode==0, r.stderr
 d=json.loads((ROOT/'reports/content_change_impact.json').read_text(encoding='utf-8'))
 assert d['readOnly'] is True and d['counts']['added']==0 and d['counts']['removed']==0 and d['counts']['changed']==0
def test_snapshot_rejects_escape():
 r=subprocess.run([sys.executable,str(ROOT/'tools/content_transaction_snapshot.py'),'../../VERSION'],cwd=ROOT,text=True,capture_output=True)
 assert r.returncode!=0 and 'REJECT outside canonical mudlib' in (r.stdout+r.stderr)
def test_snapshot_canonical_file():
 candidates=list((ROOT/'source/upstream/mudlib').rglob('*.c')); assert candidates
 rel=candidates[0].relative_to(ROOT/'source/upstream/mudlib').as_posix()
 r=subprocess.run([sys.executable,str(ROOT/'tools/content_transaction_snapshot.py'),rel,'--name','pytest'],cwd=ROOT,text=True,capture_output=True)
 assert r.returncode==0, r.stderr
 d=json.loads(r.stdout); assert d['ok'] and d['files']==1 and d['autoRestore'] is False
 # clean generated test snapshot so releases remain deterministic-ish
 (ROOT/d['snapshot']).unlink(missing_ok=True)
