from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OPEN = ROOT / "source/upstream/mudlib/cmds/std/open.c"
BANK = ROOT / "source/upstream/mudlib/std/room/bank.c"
BAZAR = ROOT / "source/upstream/mudlib/d/snow/bazar.c"


def test_global_open_routes_account_to_bank_room():
    text = OPEN.read_text(encoding="utf-8")
    assert 'arg == "account"' in text
    assert 'function_exists("do_new_account", env)' in text
    assert 'env->do_new_account(arg)' in text


def test_open_still_handles_doors_after_bank_special_case():
    text = OPEN.read_text(encoding="utf-8")
    account_pos = text.index('arg == "account"')
    door_pos = text.index('query_doors()')
    assert account_pos < door_pos
    assert 'open_door(dir)' in text


def test_bank_init_keeps_room_init_and_registers_commands():
    text = BANK.read_text(encoding="utf-8")
    assert '::init();' in text
    assert 'add_action("do_new_account", "open")' in text
    assert 'add_action("do_deposit", "deposit")' in text
    assert 'add_action("do_withdraw", "withdraw")' in text
    assert 'add_action("do_convert", "convert")' in text


def test_snow_bazar_is_bank_and_documents_open_account():
    text = BAZAR.read_text(encoding="utf-8")
    assert 'inherit BANK;' in text
    assert 'open account' in text


def test_new_account_creates_bond_and_sets_owner_balance():
    text = BANK.read_text(encoding="utf-8")
    assert 'new("/obj/bankbond")' in text
    assert 'bankbond->move(this_player())' in text
    assert 'bankbond->set("owner_id", geteuid(this_player()))' in text
    assert 'bankbond->set_balance(0)' in text
