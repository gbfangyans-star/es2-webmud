from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def text(p, enc="utf-8"): return (ROOT/p).read_text(encoding=enc, errors="replace")

def test_landing_uses_centered_art_and_aligned_hit_target():
    html=text("web/index.html")
    css=text("web/styles.css")
    assert 'class="landing-art"' in html
    assert 'aspect-ratio:1312/1199' in css
    assert "left:49.43%;top:64.76%" in css
    assert "background:#050806 url('/title_bg.png') center center/contain no-repeat" in css

def test_hud_poll_is_silent_and_colored():
    js=text("web/app.js")
    assert "hudPollInFlight" in js
    assert "return {visible:'',done:false}" in js
    assert "consumeHudPollOutput" in js
    assert "const colors={hp:'#ef6262'" in js
    assert "hud-shen" not in js  # class is generated dynamically by key, not hard-coded markup
    css=text("web/styles.css")
    assert "--hud-color" in css
    assert "::-webkit-progress-value" in css

def test_welcome_is_presentation_styled_only():
    js=text("web/app.js")
    assert "renderWelcomeIfPresent" in js
    assert '/\\[ES2 connected\\]/i' in js
    assert "login-welcome" in js
    welcome=text("source/upstream/mudlib/adm/etc/welcome")
    assert "東 方 故 事 Ⅱ" in welcome
    assert "github.com/taedlar/es2_mudlib" in welcome

def test_launchers_are_separated():
    start=text("START_ES2.bat", "ascii")
    opener=text("OPEN_ES2_BROWSER.bat", "ascii")
    assert 'start_es2_windows.ps1' in start
    assert 'start_es2_windows.ps1' in start
    assert 'http://127.0.0.1:8080' not in start
    assert 'http://127.0.0.1:8080' in opener

def test_manual_save_shortcut_became_equipment_inventory_shortcut():
    html=text("web/index.html")
    assert '<button data-cmd="inventory">裝備欄</button>' in html
    assert '<button data-cmd="save">手動存檔</button>' not in html
