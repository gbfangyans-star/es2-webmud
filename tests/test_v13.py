import subprocess,sys,tempfile,json
from pathlib import Path
ROOT=Path(__file__).parents[1]

# build_catalog must compile after v1.2 indentation regression.
for f in [ROOT/'tools/build_catalog.py',ROOT/'tools/verify_source.py',ROOT/'tools/backup_ops.py',ROOT/'tools/runtime_readiness.py']:
    subprocess.run([sys.executable,'-m','py_compile',str(f)],check=True)

# Verify source must reject a fixture/non-git source.
r=subprocess.run([sys.executable,str(ROOT/'tools/verify_source.py'),str(ROOT/'tests/fixture')],capture_output=True,text=True)
assert r.returncode!=0
x=json.loads(r.stdout)
assert x['ok'] is False and x['origin_verified'] is False

# Fixture catalog build remains allowed explicitly.
out=ROOT/'catalog/v13_fixture'
if out.exists():
    import shutil;shutil.rmtree(out)
subprocess.run([sys.executable,str(ROOT/'tools/build_catalog.py'),str(ROOT/'tests/fixture'),'-o',str(out),'--allow-fixture'],check=True)
assert (out/'all.json').exists()

print('v1.3 operator/source-gate tests passed')
