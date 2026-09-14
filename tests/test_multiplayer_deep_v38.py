from pathlib import Path
import subprocess,sys,json
ROOT=Path(__file__).resolve().parents[1]
def test_deep_multiplayer_audit():
    p=subprocess.run([sys.executable,str(ROOT/'tools/audit_multiplayer_deep.py')],capture_output=True,text=True,encoding='utf-8')
    assert p.returncode==0,p.stdout+p.stderr
    d=json.loads(p.stdout);assert d['ok'];assert len(d['checks'])>=12

def test_live_acceptance_never_stores_passwords():
    t=(ROOT/'tools/live_multiplayer_acceptance.py').read_text(encoding='utf-8')
    assert 'getpass.getpass' in t
    assert 'write_text' not in t and 'open(' not in t

def test_lan_launcher_binds_bridge_only():
    t=(ROOT/'START_ES2_LAN.bat').read_text(encoding='utf-8')
    assert 'HOST=0.0.0.0' in t
    assert 'port forwarding' in t
