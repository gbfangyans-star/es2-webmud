from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
APP = (ROOT / "web" / "app.js").read_text(encoding="utf-8")


def test_chat_capture_is_not_column_zero_only():
    assert "text.indexOf('【閒聊】')" in APP
    assert "text.slice(chatAt).trim()" in APP


def test_incoming_tell_and_reply_are_captured():
    assert "/告訴你[：﹕:]/.test(text)" in APP
    assert "/回答你[：﹕:]/.test(text)" in APP


def test_outgoing_tell_and_reply_still_captured():
    assert "/^你告訴.+[：﹕:]/.test(text)" in APP
    assert "/^你回答.+[：﹕:]/.test(text)" in APP


def test_prompt_debris_is_removed_before_logging():
    assert "text.replace(/^(?:[>＞]\\s*)+/,'').trim()" in APP
    assert "html:esc(hit.text)" in APP
