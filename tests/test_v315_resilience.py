from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def test_version():
 assert (ROOT/'VERSION').read_text().strip().startswith('3.')
def test_resilience_gate_present():
 s=(ROOT/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8')
 for x in ["threading.Barrier(2)","debugSaveErrors","glob(u+'.o.tmp*')","'重新連線' in out","getpass.getpass"]: assert x in s
def test_launcher_present(): assert (ROOT/'CHECK_MULTIPLAYER_RESILIENCE.bat').exists()
