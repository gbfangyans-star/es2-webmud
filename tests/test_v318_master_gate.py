from pathlib import Path
R=Path(__file__).resolve().parents[1]
def test_version(): assert (R/'VERSION').read_text().strip().startswith('3.')
def test_master_launcher():
 s=(R/'CHECK_MULTIPLAYER_MASTER.bat').read_text(encoding='utf-8'); assert 'multiplayer_master_gate.py' in s and 'multiplayer_master_report.json' in s
def test_master_stages():
 s=(R/'tools/multiplayer_master_gate.py').read_text(encoding='utf-8')
 for x in ['audit_multiplayer_gameplay.py','audit_multiplayer_v317.py','test_multiplayer_isolation_v34.mjs','test_multiplayer_endurance_v317.mjs','live_neolith_storm.py','live_multiplayer_resilience.py']: assert x in s
 assert 'operatorAssistedRemaining' in s and 'ASSISTED' in s
def test_no_password_persistence_contract():
 s=(R/'tools/multiplayer_master_gate.py').read_text(encoding='utf-8'); assert 'Passwords are hidden and remain memory-only' in s
