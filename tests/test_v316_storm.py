from pathlib import Path
R=Path(__file__).resolve().parents[1]
def test_version(): assert (R/'VERSION').read_text().strip().startswith('3.')
def test_storm_gate():
 s=(R/'tools/live_neolith_storm.py').read_text()
 for x in ["clientsPerWave","postStormProbe","debugErrors","socket.create_connection"]: assert x in s
 assert '--clients 50 --waves 5' in (R/'CHECK_NEOLITH_STORM.bat').read_text(errors='ignore')
def test_audit(): assert (R/'tools/audit_multiplayer_v316.py').exists()
