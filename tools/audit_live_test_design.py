#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[1]
checks=[]
def add(name, ok, detail): checks.append({'name':name,'ok':bool(ok),'detail':detail})

# Contract map: launcher must say what it really does.
contracts={
 'CHECK_MULTIPLAYER_COMBAT.bat':('static-only','audit_multiplayer_v310.py'),
 'CHECK_MULTIPLAYER_DEATH.bat':('static-only','audit_multiplayer_v311.py'),
 'CHECK_MULTIPLAYER_ROOM.bat':('live','live_multiplayer_room_acceptance.py'),
 'CHECK_MULTIPLAYER_SHARED_WORLD.bat':('live','live_multiplayer_sharedworld.py'),
 'CHECK_MULTIPLAYER_RESILIENCE.bat':('live','live_multiplayer_resilience.py'),
 'CHECK_RESTART_BEFORE.bat':('assisted','restart_recovery_snapshot.py before'),
 'CHECK_RESTART_AFTER.bat':('assisted','restart_recovery_snapshot.py after'),
 'CHECK_MULTIPLAYER_COMBAT_LIVE.bat':('assisted','live_multiplayer_combat_acceptance.py'),
 'CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat':('assisted','live_multiplayer_pvp_fight.py'),
 'CHECK_MULTIPLAYER_OFFLINE.bat':('offline','multiplayer_offline_gate.py'),
}
for fn,(kind,needle) in contracts.items():
 p=ROOT/fn;t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
 add(f'launcher:{fn}',p.exists() and needle in t and kind.upper().replace('-',' ') in t.upper(),f'{kind}; expects {needle}')

# Automated live tools must never issue destructive kill or invent world state.
for rel in ['tools/live_multiplayer_room_acceptance.py','tools/live_multiplayer_sharedworld.py','tools/live_multiplayer_resilience.py']:
 p=ROOT/rel;t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
 destructive=bool(re.search(r"\.send\(['\"](?:kill|suicide|destruct|clone|summon|teleport)\b",t,re.I))
 add('non_destructive:'+rel,p.exists() and not destructive,'no automated kill/spawn/teleport/destruct commands')

# Shared-world optional probes must remain optional and not be hard-required.
t=(ROOT/'tools/live_multiplayer_sharedworld.py').read_text(encoding='utf-8',errors='replace')
add('sharedworld_optional_item','blank=skip' in t and 'if item:' in t,'ground item probe is operator-optional')
add('sharedworld_optional_npc','blank=skip' in t and 'if npc:' in t,'NPC probe is operator-optional')

# Room guard is conditional, not hard fail.
t=(ROOT/'tools/live_multiplayer_room_acceptance.py').read_text(encoding='utf-8',errors='replace')
add('guard_is_conditional','guard relation' in t and "not x[0].startswith('guard relation')" in t,'low-level guard rejection cannot fail room acceptance')

# All socket live tools should have finite socket and wait timeouts.
for rel in ['tools/live_multiplayer_room_acceptance.py','tools/live_multiplayer_sharedworld.py','tools/live_multiplayer_resilience.py','tools/live_multiplayer_combat_acceptance.py','tools/live_multiplayer_pvp_fight.py']:
 p=ROOT/rel;t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
 add('timeouts:'+rel,p.exists() and 'socket.create_connection' in t and ('TimeoutError' in t or 'timeout=' in t),'finite connection/wait timeout present')

# Restart snapshots must use current release version dynamically, not stale hardcoded 3.17.0.
t=(ROOT/'tools/restart_recovery_snapshot.py').read_text(encoding='utf-8',errors='replace')
add('restart_version_dynamic',"read_text" in t and "VERSION" in t and "'3.17.0'" not in t,'restart reports use current VERSION file')

# Combat live tool may use fight, but must require explicit operator confirmation and must never send kill.
t=(ROOT/'tools/live_multiplayer_combat_acceptance.py').read_text(encoding='utf-8',errors='replace') if (ROOT/'tools/live_multiplayer_combat_acceptance.py').exists() else ''
add('combat_requires_confirmation','TYPE RISKY FIGHT' in t and "fight '+npc" in t and "kill '+npc" not in t,'risky NPC fight requires explicit operator confirmation; tool-issued kill is absent')
add('combat_cleanup_halt',"send('halt')" in t,'both test characters are halted after probe')

p=(ROOT/'tools/live_multiplayer_pvp_fight.py');t=p.read_text(encoding='utf-8',errors='replace') if p.exists() else ''
add('pvp_requires_mutual_consent',p.exists() and 'TYPE PVP FIGHT' in t and "A.send('fight '+ub)" in t and "B.send('fight '+ua)" in t and "send('kill" not in t,'preferred live combat gate uses mutual player fight and never kill')



# Offline development gate must explicitly refuse to claim live acceptance.
t=(ROOT/'tools/multiplayer_offline_gate.py').read_text(encoding='utf-8',errors='replace')
add('offline_gate_no_live_claim',"liveAcceptanceClaimed':False" in t and 'OFFLINE ONLY' in t,'offline gate cannot masquerade as real Windows/Neolith acceptance')
out={'version':(ROOT/'VERSION').read_text().strip(),'scope':'remaining multiplayer live-test design audit','ok':all(c['ok'] for c in checks),'checks':checks}
print(json.dumps(out,ensure_ascii=False,indent=2))
(ROOT/'reports').mkdir(exist_ok=True)
(ROOT/'reports'/'multiplayer_test_design_audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
sys.exit(0 if out['ok'] else 2)
