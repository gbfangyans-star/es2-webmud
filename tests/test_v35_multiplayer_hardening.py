from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def text(p): return (ROOT/p).read_text(encoding='utf-8')

def test_bridge_has_payload_and_slow_client_limits():
    s=text('server/index.js')
    assert 'WS_MAX_PAYLOAD_BYTES' in s
    assert 'WS_MAX_BUFFERED_BYTES' in s
    assert "maxPayload:WS_MAX_PAYLOAD_BYTES" in s
    assert 'ws.bufferedAmount>WS_MAX_BUFFERED_BYTES' in s

def test_bridge_has_aggregate_multiplayer_health_only():
    s=text('server/index.js')
    assert "'/api/multiplayer-health'" in s
    assert 'bridgeStats.peakSessions' in s
    assert 'rejectedCapacity' in s
    assert 'tcpErrors' in s

def test_bridge_has_graceful_shutdown_and_idempotent_cleanup():
    s=text('server/index.js')
    assert 'const cleanup=()=>' in s
    assert 'row.closing' in s
    assert "process.once('SIGINT',shutdown)" in s
    assert "process.once('SIGTERM',shutdown)" in s

def test_multiplayer_stress_tools_exist():
    assert (ROOT/'tests/test_multiplayer_stress_v35.mjs').exists()
    assert (ROOT/'tools/probe_neolith_concurrency.mjs').exists()
    assert (ROOT/'CHECK_MULTIPLAYER_STRESS.bat').exists()
    assert (ROOT/'CHECK_NEOLITH_CONCURRENCY.bat').exists()
    assert (ROOT/'CHECK_MULTIPLAYER_CAPACITY.bat').exists()
    assert (ROOT/'tests/test_multiplayer_capacity_v35.mjs').exists()
