from pathlib import Path
R=Path(__file__).resolve().parents[1]
def text(rel): return (R/rel).read_text(encoding='utf-8',errors='replace')
def test_tell_reply_no_missing_dns_dependency():
    for rel in ['source/upstream/mudlib/cmds/std/tell.c','source/upstream/mudlib/cmds/std/reply.c']:
        s=text(rel); assert '#include <net/dns.h>' not in s; assert '#ifdef GTELL' in s
def test_master_function_before_storm_and_identity():
    s=text('tools/multiplayer_master_gate.py'); assert s.index('Two-character tell/save/link-dead/reconnect resilience') < s.index('Real Neolith connection storm (runs last)'); assert 'Running WebMUD version identity' in s
def test_server_exposes_version_identity():
    s=text('server/index.js'); assert "/api/version" in s and 'BUILD_VERSION' in s
def test_start_is_version_safe():
    s=text('start_es2_windows.ps1'); assert 'Close the OLD WebMUD window' in s and 'Get-ListenerPid' in s
def test_banner_is_connection_phase_driven():
    s=text('web/app.js'); assert '/\\[ES2 connected\\]/i' in s and 'Do not depend on title spacing' in s
def test_isolation_uses_dynamic_ports():
    assert 'listen(0' in text('tests/test_multiplayer_isolation_v34.mjs')
