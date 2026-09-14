from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
bank=(ROOT/'source/upstream/mudlib/std/room/bank.c').read_text(encoding='utf-8')
bazar=(ROOT/'source/upstream/mudlib/d/snow/bazar.c').read_text(encoding='utf-8')

def test_exact_sign_money_word_is_supported():
    assert 'case "錢幣"' in bank
    assert 'case "文錢"' in bank
    assert 'case "碎銀"' in bank
    assert 'case "黃金"' in bank

def test_deposit_resolves_real_money_objects_not_plain_id_collision():
    assert 'object find_player_money' in bank
    assert 'inherits(MONEY, ob)' in bank
    assert 'ob->query("money_id") == id' in bank
    assert 'find_player_money(this_player(), money)' in bank

def test_withdraw_uses_whitelist_money_factory():
    assert 'string money_file' in bank
    assert 'if( id!="coin" && id!="silver" && id!="gold" ) return 0;' in bank
    assert 'new(money_file(money))' in bank

def test_bank_sign_has_literal_examples():
    assert 'deposit 25 文錢' in bazar
    assert 'withdraw 10 文錢' in bazar
