import subprocess,sys,json
from pathlib import Path
ROOT=Path(__file__).parents[1]
subprocess.run([sys.executable,'-m','py_compile',str(ROOT/'tools/preflight.py')],check=True)
print('v2.0 preflight compile test passed')
