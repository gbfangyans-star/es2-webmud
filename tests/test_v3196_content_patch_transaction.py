from pathlib import Path
import subprocess,sys,json,hashlib,tempfile
ROOT=Path(__file__).resolve().parents[1]
TOOL=ROOT/'tools/content_patch_transaction.py'
def h(b): return hashlib.sha256(b).hexdigest()
def run(plan,*args): return subprocess.run([sys.executable,str(TOOL),str(plan),*args],cwd=ROOT,text=True,capture_output=True)
def test_transaction_tool_is_dry_run_and_does_not_modify_canonical(tmp_path):
    target=ROOT/'source/upstream/mudlib/std/char.c'; before=target.read_bytes()
    plan=tmp_path/'p.json'; plan.write_text(json.dumps({'sourceBoundary':'taedlar/es2_mudlib only','files':[{'path':'std/char.c','expectedBeforeSha256':h(before),'replacementText':before.decode('utf-8')+'\n'}]}),encoding='utf-8')
    r=run(plan); assert r.returncode==0; assert json.loads(r.stdout)['dryRun'] is True; assert target.read_bytes()==before
def test_transaction_rejects_stale_sha(tmp_path):
    plan=tmp_path/'p.json'; plan.write_text(json.dumps({'sourceBoundary':'taedlar/es2_mudlib only','files':[{'path':'std/char.c','expectedBeforeSha256':'0'*64,'replacementText':'x'}]}),encoding='utf-8')
    r=run(plan); assert r.returncode!=0; assert 'stale SHA' in (r.stdout+r.stderr)
def test_transaction_rejects_escape(tmp_path):
    plan=tmp_path/'p.json'; plan.write_text(json.dumps({'sourceBoundary':'taedlar/es2_mudlib only','files':[{'path':'../VERSION','expectedBeforeSha256':'0'*64,'replacementText':'x'}]}),encoding='utf-8')
    r=run(plan); assert r.returncode!=0; assert 'outside canonical mudlib' in (r.stdout+r.stderr)
def test_transaction_rejects_wrong_boundary(tmp_path):
    plan=tmp_path/'p.json'; plan.write_text(json.dumps({'sourceBoundary':'other','files':[{'path':'std/char.c','expectedBeforeSha256':'0'*64,'replacementText':'x'}]}),encoding='utf-8')
    r=run(plan); assert r.returncode!=0; assert 'sourceBoundary mismatch' in (r.stdout+r.stderr)
