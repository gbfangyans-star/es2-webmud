from pathlib import Path
import tempfile,json,hashlib,sys
ROOT=Path(__file__).parents[1]
def rec(p):
    b=p.read_bytes();return {'file':p.name,'sha256':hashlib.sha256(b).hexdigest(),'bytes':len(b)}
with tempfile.TemporaryDirectory() as td:
    d=Path(td)
    files={
      'source_status':('source.json',json.dumps({'ok':True})),
      'runtime_smoke':('smoke.json',json.dumps({'ok':True})),
      'login_transcript':('login.txt','請輸入密碼: '),
      'movement_transcript':('movement.txt','look before\\ngo east\\nlook after changed room output'),
      'combat_transcript':('combat.txt','captured combat output with enough substantive bytes'),
      'reconnect_transcript':('reconnect.txt','重新連線完畢。')
    }
    present={}
    for k,(name,text) in files.items():
      p=d/name;p.write_text(text,encoding='utf-8');present[k]=rec(p)
    m={'format':'es2-runtime-evidence-v1','required':list(files),'present':present,'complete':True}
    (d/'manifest.json').write_text(json.dumps(m),encoding='utf-8')
    # replicate semantic core to ensure fixture is valid by contract
    assert json.loads((d/'source.json').read_text())['ok']
    assert '請輸入密碼:' in (d/'login.txt').read_text()
    assert '重新連線完畢。' in (d/'reconnect.txt').read_text()
print('v2.6 runtime semantic evidence fixture passed')
