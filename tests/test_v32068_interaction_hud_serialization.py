from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
APP=(ROOT/'web/app.js').read_text(encoding='utf-8')

def test_user_commands_wait_for_hud_end():
    assert 'let pendingUserCommands = [];' in APP
    assert 'if(hudPollInFlight)' in APP
    assert 'pendingUserCommands.push({command:c,sensitive})' in APP
    assert 'flushPendingUserCommands();' in APP

def test_duplicate_clicks_are_not_queued_repeatedly():
    assert 'pendingUserCommands.some(x=>x.command===c&&x.sensitive===sensitive)' in APP

def test_interaction_panel_uses_delegated_click_handler():
    assert "root.addEventListener('click',e=>" in APP
    assert "e.target.closest('.context-item-action[data-command]')" in APP
    assert 'send(command);' in APP
