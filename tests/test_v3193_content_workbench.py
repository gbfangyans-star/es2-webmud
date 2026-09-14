from pathlib import Path
import json, subprocess, sys
ROOT=Path(__file__).resolve().parents[1]

def test_workbench_builder_and_boundary():
    p=subprocess.run([sys.executable,str(ROOT/'tools/build_content_workbench.py')],cwd=ROOT,capture_output=True,text=True)
    assert p.returncode==0,p.stdout+p.stderr
    d=json.loads((ROOT/'catalog/generated/content_workbench.json').read_text(encoding='utf-8'))
    assert d['readOnlyIndex'] is True
    assert d['sourceBoundary']=='taedlar/es2_mudlib only'
    assert d['summary']['entities']>0
    assert d['summary']['manualReviewEntities']==len(d['manualReview'])
    assert all(x.get('path') and x.get('reasons') for x in d['manualReview'])

def test_workbench_ui_uses_existing_read_apis_only():
    js=(ROOT/'web/workbench.js').read_text(encoding='utf-8')
    assert '/api/catalog?file=content_workbench.json' in js
    assert '/api/entity?path=' in js and '/api/relations?path=' in js and '/api/source?path=' in js
    assert "method:'PUT'" not in js and 'method:"PUT"' not in js
    assert "method:'POST'" not in js and 'method:"POST"' not in js

def test_multiplayer_implementing_files_untouched_by_workbench_build():
    # Build operation must not write bridge or canonical gameplay source.
    before=(ROOT/'server/index.js').read_bytes()
    mud=(ROOT/'source/upstream/mudlib/cmds/std/tell.c').read_bytes()
    subprocess.check_call([sys.executable,str(ROOT/'tools/build_content_workbench.py')],cwd=ROOT)
    assert (ROOT/'server/index.js').read_bytes()==before
    assert (ROOT/'source/upstream/mudlib/cmds/std/tell.c').read_bytes()==mud
