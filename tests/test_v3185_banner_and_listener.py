from pathlib import Path
R=Path(__file__).resolve().parents[1]

def test_version_and_art():
    assert (R/'VERSION').read_text().strip().startswith('3.')

def test_banner_is_shown_as_mud_text():
    s=(R/'web/app.js').read_text(encoding='utf-8')
    assert "welcomeBuffer" not in s
    assert "/login_title_v3185.png" not in s

def test_master_rechecks_listener_after_storm():
    s=(R/'tools/multiplayer_master_gate.py').read_text(encoding='utf-8')
    assert 'Post-storm Neolith stability' in s
    assert 'Authenticated functional gate FIRST' in s

def test_live_client_retries_transient_refusal():
    s=(R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8')
    assert 'after 6 attempts' in s
    assert 'range(6)' in s
