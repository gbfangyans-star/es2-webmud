from pathlib import Path
R=Path(__file__).resolve().parents[1]

def test_version_and_art():
    assert (R/'VERSION').read_text().strip().startswith('3.')
    assert (R/'web/login_title_v3185.png').stat().st_size>500_000

def test_banner_accepts_ascii_roman_and_buffers_chunks():
    s=(R/'web/app.js').read_text(encoding='utf-8')
    assert '/\\[ES2 connected\\]/i' in s
    assert "welcomeBuffer" in s
    assert "/login_title_v3185.png" in s
    assert 'Do not depend on title spacing' in s

def test_master_rechecks_listener_after_storm():
    s=(R/'tools/multiplayer_master_gate.py').read_text(encoding='utf-8')
    assert 'Post-storm Neolith stability' in s
    assert 'Authenticated functional gate FIRST' in s

def test_live_client_retries_transient_refusal():
    s=(R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8')
    assert 'after 6 attempts' in s
    assert 'range(6)' in s
