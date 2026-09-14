from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def read(rel): return (ROOT/rel).read_text(encoding="utf-8")

def test_bank_accepts_chinese_and_english_currency_names():
    s=read("source/upstream/mudlib/std/room/bank.c")
    for token in ['"coin"','"文錢"','"銅錢"','"silver"','"碎銀"','"gold"','"黃金"']:
        assert token in s
    assert 'money = normalize_money_id(money);' in s
    assert 'from = normalize_money_id(from);' in s
    assert 'to = normalize_money_id(to);' in s

def test_bank_bond_lookup_uses_unambiguous_assignment():
    s=read("source/upstream/mudlib/std/room/bank.c")
    assert 'if( !(bond = present("bankbond", this_player())) )' in s
    assert 'if( !bond = present("bankbond", this_player()) )' not in s

def test_combat_hud_uses_ten_segments():
    s=read("web/app.js")
    block=s[s.index("function combatStat"):s.index("function combatCard")]
    assert "const segments=10" in block
    assert "25" not in block
