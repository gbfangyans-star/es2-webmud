from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ATTACK = ROOT / 'source/upstream/mudlib/feature/char/attack.c'


def test_low_intimidate_still_builds_attack_patience():
    text = ATTACK.read_text()
    assert 'attack_patience += (intimidate / 10 > 0) ? intimidate / 10 : 1;' in text
    assert 'attack_patience += intimidate / 10;' not in text


def test_attack_chance_floor_and_success_reset_are_preserved():
    text = ATTACK.read_text()
    assert 'if( chance < 20 ) chance = 20;' in text
    assert 'else if( chance > 80 ) chance = 80;' in text
    assert 'attack_patience = 0;' in text
