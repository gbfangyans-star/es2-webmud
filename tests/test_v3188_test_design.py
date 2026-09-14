from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def read(rel): return (ROOT/rel).read_text(encoding='utf-8',errors='replace')

def test_combat_launcher_is_explicit_static_only():
 t=read('CHECK_MULTIPLAYER_COMBAT.bat')
 assert 'STATIC ONLY' in t and 'audit_multiplayer_v310.py' in t

def test_live_combat_launcher_is_assisted_and_nonlethal():
 t=read('CHECK_MULTIPLAYER_COMBAT_LIVE.bat')
 assert 'ASSISTED LIVE' in t and 'live_multiplayer_combat_acceptance.py' in t
 py=read('tools/live_multiplayer_combat_acceptance.py')
 assert 'TYPE RISKY FIGHT' in py
 assert "send('halt')" in py
 assert "kill '+npc" not in py
 assert "send('kill" not in py

def test_death_launcher_does_not_claim_live():
 t=read('CHECK_MULTIPLAYER_DEATH.bat')
 assert 'STATIC ONLY' in t
 assert 'audit_multiplayer_v311.py' in t

def test_restart_report_version_is_dynamic():
 t=read('tools/restart_recovery_snapshot.py')
 assert "root/'VERSION'" in t
 assert "'3.17.0'" not in t

def test_design_audit_exists():
 t=read('tools/audit_live_test_design.py')
 assert 'remaining multiplayer live-test design audit' in t
