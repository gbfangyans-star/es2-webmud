from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
APP=(ROOT/'web/app.js').read_text(encoding='utf-8')

def test_player_click_has_bounded_hud_wait():
    assert 'const HUD_ACTION_FLUSH_MS = 180;' in APP
    assert 'setTimeout(()=>{' in APP
    assert 'flushPendingUserCommands();' in APP
    assert 'if(hudPollInFlight)' in APP

def test_hud_has_real_timeout_timer():
    assert 'let hudResponseTimer = null;' in APP
    assert 'hudResponseTimer=setTimeout' in APP
    assert 'HUD_POLL_TIMEOUT_MS' in APP

def test_interaction_buttons_use_delegated_send():
    assert "root.addEventListener('click'" in APP
    assert "send(command);" in APP
