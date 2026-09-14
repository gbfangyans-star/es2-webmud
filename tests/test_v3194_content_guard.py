from pathlib import Path
import json,subprocess,sys,tempfile
ROOT=Path(__file__).resolve().parents[1]
def test_content_guard_current_tree_matches_baseline():
 p=subprocess.run([sys.executable,str(ROOT/'tools/content_change_guard.py')],cwd=ROOT,capture_output=True,text=True); assert p.returncode==0,p.stdout+p.stderr
 d=json.loads((ROOT/'reports/content_source_change.json').read_text(encoding='utf-8')); assert d['ok'] and d['counts']=={'added':0,'removed':0,'changed':0}
def test_intake_plan_is_read_only_and_bounded():
 p=subprocess.run([sys.executable,str(ROOT/'tools/content_intake_plan.py')],cwd=ROOT,capture_output=True,text=True); assert p.returncode==0
 d=json.loads((ROOT/'reports/content_intake_plan.json').read_text(encoding='utf-8')); assert d['readOnly'] is True; assert d['sourceBoundary']=='taedlar/es2_mudlib only'; assert d['canonicalEntities']>0; assert d['manualReview']>=0
def test_guard_does_not_modify_canonical_or_bridge():
 mud=ROOT/'source/upstream/mudlib/cmds/std/tell.c'; bridge=ROOT/'server/index.js'; before=(mud.read_bytes(),bridge.read_bytes())
 subprocess.check_call([sys.executable,str(ROOT/'tools/content_change_guard.py')],cwd=ROOT); subprocess.check_call([sys.executable,str(ROOT/'tools/content_intake_plan.py')],cwd=ROOT)
 assert before==(mud.read_bytes(),bridge.read_bytes())
def test_windows_guard_is_non_mutating_command_set():
 s=(ROOT/'CHECK_CONTENT_GUARD.bat').read_text(encoding='utf-8').lower(); assert 'content_change_guard.py --write-baseline' not in s; assert 'content_change_guard.py' in s
