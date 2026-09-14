#!/usr/bin/env python3
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
p = ROOT / "reports" / "oldpine_dynamic_topology_v1.json"
data = json.loads(p.read_text(encoding="utf-8"))
checks = []
def ok(name, cond):
    checks.append((name, bool(cond)))

ok("archaeology boundary", data.get("playable_merge") is False)
ok("cave dynamic", data["dynamic_groups"]["cave_maze"]["dynamic"] is True)
ok("pine dynamic", data["dynamic_groups"]["pine_maze"]["dynamic"] is True)
fixed = {tuple(x) for x in data["dynamic_groups"]["pine_maze"]["fixed_edges"]}
ok("pine2 keep1", ("pine2","east","keep1") in fixed)
ok("pine7 cliffdown", ("pine7","southwest","cliffdown") in fixed)
actions = {(x.get("room"),x.get("verb"),x.get("destination")) for x in data["special_actions"]}
ok("vine action present", any(x.get("room")=="epath2" and x.get("success_destination")=="passage" and x.get("failure_destination")=="waterfall" for x in data["special_actions"]))
ok("clearing tree climb", ("clearing","climb pine","tree1") in actions)
ok("cliff to water", ("cliff1","climb down","riverbank1") in actions)
ok("keep callback", any(x.get("room")=="keep2" and x.get("callback")=="pipe_notify" for x in data["event_callbacks"]))
ok("pipe object callback", any(x.get("object")=="bamboo_pipe" for x in data["event_callbacks"]))

for name, result in checks:
    print(("PASS" if result else "FAIL") + " - " + name)
if not all(r for _, r in checks):
    raise SystemExit(1)
print(f"PASS {sum(r for _,r in checks)}/{len(checks)} checks")
