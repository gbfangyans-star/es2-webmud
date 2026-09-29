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


def test_snow_bazar_is_bank_and_documents_account_free_banking():
    text = BAZAR.read_text(encoding="utf-8")
    assert 'inherit BANK;' in text
    assert 'balance' in text
    assert 'open account' not in text
    assert '不需開戶' in text


def test_open_account_no_longer_creates_a_bond():
    text = BANK.read_text(encoding="utf-8")
    block = text[text.index('int do_new_account'):text.index('int do_convert')]
    assert 'bankbond' not in block.replace('retire_bankbond', '')
    assert '不需要開戶' in block
