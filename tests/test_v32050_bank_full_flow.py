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
    for verb, fn in [('deposit','do_deposit'),('withdraw','do_withdraw')]:
        s = text(f'cmds/std/{verb}.c')
        assert f'function_exists("{fn}", env)' in s
        assert f'env->{fn}(arg)' in s


def test_player_command_path_can_find_bank_bridges():
    s = text('include/command.h')
    plr = s[s.index('#define PLR_PATH'):s.index('#define NPC_PATH')]
    assert '"/cmds/std/"' in plr


def test_deposit_credits_character_account_without_a_bond():
    s = text('std/room/bank.c')
    block = s[s.index('int do_deposit'):s.index('int do_withdraw')]
    assert 'if( amount <= 0 )' in block
    assert 'value = amount * money_ob->query("base_value");' in block
    assert 'this_player()->add("bank_account", value);' in block
    assert 'money_ob->add_amount( - amount );' in block
    assert 'present("bankbond"' not in block


def test_withdraw_checks_character_account_and_uses_money_file():
    s = text('std/room/bank.c')
    block = s[s.index('int do_withdraw'):]
    assert 'if( amount <= 0 )' in block
    assert 'money_ob = new(money_file(money))' in block
    assert 'this_player()->query("bank_account") < money_ob->value()' in block
    assert 'this_player()->add("bank_account", - money_ob->value());' in block
    assert 'present("bankbond"' not in block


def test_withdraw_rolls_back_balance_when_inventory_cannot_take_money():
    s = text('std/room/bank.c')
    block = s[s.index('if( !money_ob->move(this_player()) )'):]
    assert 'this_player()->add("bank_account", money_ob->value());' in block
    assert 'destruct(money_ob);' in block


def test_balance_command_reads_character_account_anywhere():
    s = text('cmds/std/balance.c')
    assert 'me->query("bank_account")' in s
    assert 'string money_string(int amount)' in s
    assert 'BALANCE_CMD->money_string(amount)' in text('std/room/bank.c')


def test_old_bankbond_expires_on_login_and_is_not_saved_again():
    s = text('obj/bankbond.c')
    assert 'string query_autoload() { return 0; }' in s
    assert 'call_out("expire", 1);' in s
    assert 'destruct(this_object());' in s


def test_money_denominations_are_consistent():
    coin = text('obj/money/coin.c')
    silver = text('obj/money/silver.c')
    gold = text('obj/money/gold.c')
    assert 'set("base_value", 1)' in coin
    assert 'set("base_value", 100)' in silver
    assert 'set("base_value", 10000' in gold


def test_convert_validates_source_and_target_and_deducts_source():
    s = text('std/room/bank.c')
    assert 'from_ob = find_player_money(this_player(), from);' in s
    assert 'if( !money_file(to) )' in s
    assert 'from_ob->add_amount(-amount);' in s
