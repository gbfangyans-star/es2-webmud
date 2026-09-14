from pathlib import Path
R=Path(__file__).resolve().parents[1]

def test_version_and_preserved_live_characters():
 assert (R/'VERSION').read_text().strip().startswith('3.')
 for u in ('wolfer','wolfer1'):
  assert (R/'source/upstream/mudlib/data/user'/u[0]/(u+'.o')).exists()
  assert (R/'source/upstream/mudlib/data/login'/u[0]/(u+'.o')).exists()

def test_live_gate_has_visible_progress_and_bounded_waits():
 s=(R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8')
 assert "progress('LOGIN: connecting both characters...')" in s
 assert 'LOGIN phase exceeded 40 seconds' in s
 assert "progress(f'WAVE {i}/{max(1,a.waves)}" in s
 assert 'deadline=time.monotonic()+4.25' in s
 assert 'sender.read(.10)' in s and 'recipient.read(.10)' in s
 assert 'concurrent save phase exceeded 6 seconds' in s

def test_approved_title_art_is_bundled_and_rendered():
 assert (R/'web/login_title_v3185.png').stat().st_size>100000
 app=(R/'web/app.js').read_text(encoding='utf-8')
 css=(R/'web/styles.css').read_text(encoding='utf-8')
 assert '/login_title_v3185.png' in app
 assert 'login-welcome-art' in app
 assert '.login-title-art' in css
