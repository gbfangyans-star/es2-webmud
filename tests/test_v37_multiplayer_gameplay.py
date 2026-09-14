from pathlib import Path
import subprocess,sys
ROOT=Path(__file__).resolve().parents[1]
def test_multiplayer_gameplay_contracts():
    r=subprocess.run([sys.executable,str(ROOT/'tools/audit_multiplayer_gameplay.py')],cwd=ROOT,capture_output=True,text=True)
    assert r.returncode==0, r.stdout+r.stderr
def test_multiplayer_acceptance_assets():
    assert (ROOT/'CHECK_MULTIPLAYER_GAMEPLAY.bat').exists()
    s=(ROOT/'MULTIPLAYER_STATUS.md').read_text(encoding='utf-8')
    assert 'say' in s and 'tell' in s and 'reconnect' in s and '10+' in s
