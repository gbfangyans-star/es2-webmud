import subprocess,sys,json
from pathlib import Path
ROOT=Path(__file__).parents[1]
subprocess.run([sys.executable,'-m','py_compile',str(ROOT/'tools/audit_multiplayer_bridge.py')],check=True)
r=subprocess.run([sys.executable,str(ROOT/'tools/audit_multiplayer_bridge.py'),str(ROOT/'server/index.js')],capture_output=True,text=True,check=True)
x=json.loads(r.stdout);assert x['ok'] is True
print('v2.1 multiplayer bridge audit passed')
