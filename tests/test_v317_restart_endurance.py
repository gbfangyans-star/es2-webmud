from pathlib import Path
R=Path(__file__).resolve().parents[1]
def test_version(): assert (R/'VERSION').read_text().strip().startswith('3.')
def test_endurance():
 s=(R/'tests/test_multiplayer_endurance_v317.mjs').read_text();assert 'waves=20, perWave=25' in s and 'crossTalk' in s and 'sessions.active===0' in s
def test_restart_snapshot():
 s=(R/'tools/restart_recovery_snapshot.py').read_text();assert "choices=['before','after']" in s and 'changedAcrossRestart' in s and 'orphanTmp' in s
def test_launchers(): assert (R/'CHECK_RESTART_BEFORE.bat').exists() and (R/'CHECK_RESTART_AFTER.bat').exists() and (R/'CHECK_MULTIPLAYER_ENDURANCE.bat').exists()
