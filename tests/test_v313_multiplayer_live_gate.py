from pathlib import Path
import subprocess,sys
R=Path(__file__).resolve().parents[1]
def test_v313_canonical_audit():
 r=subprocess.run([sys.executable,str(R/'tools/audit_multiplayer_v313.py')],cwd=R,capture_output=True,text=True)
 assert r.returncode==0, r.stdout+r.stderr
 assert '"ok": true' in r.stdout
def test_room_live_gate_is_non_destructive_and_password_safe():
 t=(R/'tools/live_multiplayer_room_acceptance.py').read_text(encoding='utf-8')
 assert 'getpass.getpass' in t
 assert "goto /d/" not in t
 assert "send('say '+token)" in t
 assert "send('team with '+ub)" in t
 assert "send('follow '+ua)" in t
 assert "send('guard '+ub)" in t
 assert 'Password' not in (R/'CHECK_MULTIPLAYER_ROOM.bat').read_text(encoding='utf-8') or 'Passwords are hidden' in (R/'CHECK_MULTIPLAYER_ROOM.bat').read_text(encoding='utf-8')
