from pathlib import Path
R=Path(__file__).parents[1]
app=(R/"web/app.js").read_text(encoding="utf-8")
html=(R/"web/index.html").read_text(encoding="utf-8")
assert "renderScoreHUD" in app
for x in ["形體","精","氣","神","食物","飲水","疲勞"]:
    assert x in app
assert 'id="scoreHud"' in html
print("v0.8 HUD source checks passed")
