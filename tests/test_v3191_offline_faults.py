from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def test_fault_matrix_is_wired_into_offline_gate():
    s=(ROOT/'tools/multiplayer_offline_gate.py').read_text(encoding='utf-8')
    assert 'test_multiplayer_fault_matrix_v3191.mjs' in s
    assert 'multiplayer_evidence_carryforward.py' in s

def test_fault_launcher_and_report_contract_exist():
    assert (ROOT/'CHECK_MULTIPLAYER_FAULTS.bat').exists()
    s=(ROOT/'tests/test_multiplayer_fault_matrix_v3191.mjs').read_text(encoding='utf-8')
    for name in ['backend-unavailable-cleanup','backend-disconnect-propagates','abrupt-client-disconnect-cleanup','one-backend-failure-does-not-cross-kill','oversize-websocket-is-contained']:
        assert name in s
    assert 'liveAcceptanceClaimed:false' in s

def test_carryforward_is_fail_closed():
    s=(ROOT/'tools/multiplayer_evidence_carryforward.py').read_text(encoding='utf-8')
    assert "return 0 if out['ok'] else 4" in s
    assert 'coveredGateFingerprints' in s
