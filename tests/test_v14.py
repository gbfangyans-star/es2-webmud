import subprocess,sys,tempfile,json
from pathlib import Path
ROOT=Path(__file__).parents[1]

for f in [
 ROOT/'tools/runtime_probe.py',
 ROOT/'tools/runtime_smoke.py',
 ROOT/'tools/validate_login_transcript.py',
 ROOT/'tools/runtime_readiness.py',
 ROOT/'tools/build_catalog.py',
]:
    subprocess.run([sys.executable,'-m','py_compile',str(f)],check=True)

with tempfile.TemporaryDirectory() as td:
    p=Path(td)/'existing.txt'
    p.write_text('歡迎\\n請輸入密碼: ',encoding='utf-8')
    r=subprocess.run([sys.executable,str(ROOT/'tools/validate_login_transcript.py'),str(p)],capture_output=True,text=True)
    assert r.returncode==0
    assert json.loads(r.stdout)['flow']=='existing'

    p2=Path(td)/'new.txt'
    p2.write_text('請設定您的密碼: \\n請再輸入一次您的密碼，以確認您沒記錯:\\n您的電子郵件地址 (或 none):\\n選擇你的角色所屬的種族: \\n您的顯示名稱: ',encoding='utf-8')
    r=subprocess.run([sys.executable,str(ROOT/'tools/validate_login_transcript.py'),str(p2)],capture_output=True,text=True)
    assert r.returncode==0
    assert json.loads(r.stdout)['flow']=='new_character'

# Closed port must fail cleanly, not hang.
r=subprocess.run([sys.executable,str(ROOT/'tools/runtime_probe.py'),'--host','127.0.0.1','--port','1','--timeout','0.2'],capture_output=True,text=True,timeout=3)
assert r.returncode!=0
x=json.loads(r.stdout)
assert x['connected'] is False and x['ok'] is False

print('v1.4 runtime smoke tests passed')
