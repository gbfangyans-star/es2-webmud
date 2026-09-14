from pathlib import Path
import importlib.util,tempfile,json,subprocess,sys
BASE=Path(__file__).parents[1]
def load(name,file):
    s=importlib.util.spec_from_file_location(name,file);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
idx=load('idx2',BASE/'tools/index_es2.py')
fixture=BASE/'tests/fixture';mudlib,meta=idx.verify_repo(fixture,strict_remote=False)
rows=[idx.extract(p,mudlib) for p in mudlib.rglob('*') if p.is_file() and p.suffix in {'.c','.h'}]
with tempfile.TemporaryDirectory() as td:
    out=Path(td);idx.write_indexes(rows,out,meta)
    subprocess.run([sys.executable,str(BASE/'tools/build_views.py'),str(out)],check=True,capture_output=True,text=True)
    graph=json.loads((out/'world_graph.json').read_text(encoding='utf-8'))
    assert any(e['direction']=='east' and e['resolved'] for e in graph['edges'])
    summary=json.loads((out/'browser_summary.json').read_text(encoding='utf-8'))
    assert summary['counts']['room']==3
print('browser view tests passed')
