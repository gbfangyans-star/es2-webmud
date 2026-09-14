#!/usr/bin/env python3
from pathlib import Path
import json,sys
R=Path(__file__).resolve().parents[1]
checks={
 'storm_tool':(R/'tools/live_neolith_storm.py').exists(),
 'storm_launcher':(R/'CHECK_NEOLITH_STORM.bat').exists(),
 'storm_50x5':'--clients 50 --waves 5' in (R/'CHECK_NEOLITH_STORM.bat').read_text(encoding='utf-8',errors='ignore'),
 'post_storm_probe':'postStormProbe' in (R/'tools/live_neolith_storm.py').read_text(encoding='utf-8',errors='replace'),
 'driver_debug_scan':'debugErrors' in (R/'tools/live_neolith_storm.py').read_text(encoding='utf-8',errors='replace'),
 'resilience_gate':(R/'tools/live_multiplayer_resilience.py').exists(),
 'save_collision_barrier':'threading.Barrier(2)' in (R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8',errors='replace'),
 'orphan_tmp_rejection':"glob(u+'.o.tmp*')" in (R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8',errors='replace'),
 'abrupt_reconnect':"A.close();time.sleep(.7)" in (R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8',errors='replace'),
 'bridge_stress':(R/'tests/test_multiplayer_stress_v35.mjs').exists(),
 'bridge_capacity':(R/'tests/test_multiplayer_capacity_v35.mjs').exists(),
 'real_driver_concurrency':(R/'tools/probe_neolith_concurrency.mjs').exists(),
}
out={'version':(R/'VERSION').read_text(encoding='utf-8').strip(),'passed':sum(checks.values()),'total':len(checks),'checks':checks,'ok':all(checks.values())}
print(json.dumps(out,indent=2));sys.exit(0 if out['ok'] else 2)
