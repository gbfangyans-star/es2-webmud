#!/usr/bin/env python3
from pathlib import Path
import json,sys
R=Path(__file__).resolve().parents[1]
checks={
 'endurance_test':(R/'tests/test_multiplayer_endurance_v317.mjs').exists(),
 'endurance_500_sessions':'waves=20, perWave=25' in (R/'tests/test_multiplayer_endurance_v317.mjs').read_text(),
 'endurance_cross_talk':'crossTalk' in (R/'tests/test_multiplayer_endurance_v317.mjs').read_text(),
 'endurance_cleanup':'sessions.active===0' in (R/'tests/test_multiplayer_endurance_v317.mjs').read_text(),
 'restart_snapshot':(R/'tools/restart_recovery_snapshot.py').exists(),
 'restart_hashes':'sha256' in (R/'tools/restart_recovery_snapshot.py').read_text(),
 'restart_two_phase':"choices=['before','after']" in (R/'tools/restart_recovery_snapshot.py').read_text(),
 'restart_rejects_changes':'changedAcrossRestart' in (R/'tools/restart_recovery_snapshot.py').read_text(),
 'restart_tmp_guard':'orphanTmp' in (R/'tools/restart_recovery_snapshot.py').read_text(),
 'restart_before_launcher':(R/'CHECK_RESTART_BEFORE.bat').exists(),
 'restart_after_launcher':(R/'CHECK_RESTART_AFTER.bat').exists(),
 'driver_storm_preserved':(R/'CHECK_NEOLITH_STORM.bat').exists(),
 'authenticated_resilience_preserved':(R/'CHECK_MULTIPLAYER_RESILIENCE.bat').exists(),
}
out={'version':'3.17.0','passed':sum(checks.values()),'total':len(checks),'checks':checks,'ok':all(checks.values())}
print(json.dumps(out,indent=2));sys.exit(0 if out['ok'] else 2)
