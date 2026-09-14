from pathlib import Path
R=Path(__file__).resolve().parents[1]

def test_runtime_identity_is_current_root_relative():
    v=(R/"VERSION").read_text(encoding="utf-8").strip()
    assert R.name == f"ES2_WebMUD_SourceOnly_v{v}"
    assert v.startswith("3.")
