from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / 'source' / 'upstream' / 'mudlib'


def text(rel):
    return (MUD / rel).read_text(encoding='utf-8')


def test_bank_room_registers_all_four_actions():
    s = text('std/room/bank.c')
    for fn, verb in [('do_convert','convert'),('do_deposit','deposit'),('do_withdraw','withdraw'),('do_new_account','open')]:
        assert f'add_action("{fn}", "{verb}")' in s


def test_global_command_bridges_exist_for_bank_commands():
    for verb, fn in [('deposit','do_deposit'),('withdraw','do_withdraw'),('convert','do_convert')]:
        s = text(f'cmds/std/{verb}.c')
        assert f'function_exists("{fn}", env)' in s
        assert f'env->{fn}(arg)' in s


def test_player_command_path_can_find_bank_bridges():
    s = text('include/command.h')
    assert '#define PLR_PATH ({"/cmds/std/", "/cmds/usr/"})' in s


def test_deposit_rejects_zero_and_negative_and_uses_base_value():
    s = text('std/room/bank.c')
    assert 'if( amount <= 0 )' in s
    assert 'bond->transact(amount * money_ob->query("base_value"));' in s
    assert 'money_ob->add_amount( - amount );' in s


def test_withdraw_rejects_zero_and_negative_and_uses_absolute_money_path():
    s = text('std/room/bank.c')
    assert s.count('if( amount <= 0 )') >= 2
    assert 'file_size("/obj/money/" + money + ".c")' in s
    assert 'money_ob = new("/obj/money/" + money)' in s
    assert 'bond->transact(- money_ob->value());' in s


def test_withdraw_rolls_back_balance_when_inventory_cannot_take_money():
    s = text('std/room/bank.c')
    block = s[s.index('if( !money_ob->move(this_player()) )'):]
    assert 'bond->transact(money_ob->value());' in block
    assert 'destruct(money_ob);' in block


def test_bankbond_transaction_keeps_character_account_in_sync():
    s = text('obj/bankbond.c')
    assert 'balance = environment()->query("bank_account") + amount;' in s
    assert 'environment()->set("bank_account", balance);' in s


def test_money_denominations_are_consistent():
    coin = text('obj/money/coin.c')
    silver = text('obj/money/silver.c')
    gold = text('obj/money/gold.c')
    assert 'set("base_value", 1)' in coin
    assert 'set("base_value", 100)' in silver
    assert 'set("base_value", 10000' in gold


def test_convert_validates_source_and_target_and_deducts_source():
    s = text('std/room/bank.c')
    assert 'present(from + "_money", this_player())' in s
    assert 'file_size("/obj/money/" + to + ".c") < 0' in s
    assert 'from_ob->add_amount(-amount);' in s
