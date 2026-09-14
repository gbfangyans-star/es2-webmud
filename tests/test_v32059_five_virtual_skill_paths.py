"""Five deterministic player-path simulations for restored skill EXP.
These model the exact formulas while source-wiring tests verify the LPC hooks.
They are not a substitute for a live Neolith/TELNET gate.
"""
import random

def D(pl, ml): return max(2, min(10, ml-pl))
def ib(i): return i//7

def defense_gain(rng, pl, ml, intel):
    d=D(pl,ml)
    return (rng.randrange(d)+1)*(rng.randrange(d)+1)*ib(intel)

def blade_gain(rng, intel):
    return (rng.randrange(intel)+1)*ib(intel) if intel > 0 else ib(intel)

def unarmed_gain(rng, strength):
    if strength <= 0: return 0
    return (rng.randrange(strength)+1)*(rng.randrange(strength)+1)+rng.randrange(strength)

def run(seed, player):
    rng=random.Random(seed)
    pl,ml,intel,strength,cps,cor=player
    return {
        'D':D(pl,ml),
        'dodge':defense_gain(rng,pl,ml,intel),
        'parry':defense_gain(rng,pl,ml,intel),
        'unarmed':unarmed_gain(rng,strength),
        'blade':blade_gain(rng,intel),
        'tiger_force_hit':blade_gain(rng,intel)+(rng.randrange(cps) if cps>0 else 0),
        'tiger_blade_hit':blade_gain(rng,intel)+(rng.randrange(cor) if cor>0 else 0),
    }

def test_five_virtual_players_cover_low_equal_mid_high_and_overcap_mobs():
    players=[
        (1,1,7,10,8,9),      # same level => D2
        (10,5,14,15,12,13),  # lower mob => D2
        (10,12,21,18,17,16), # +2 => D2
        (10,15,28,20,19,18), # +5 => D5
        (10,40,35,24,22,21), # +30 => D10 cap
    ]
    rows=[run(100+i,p) for i,p in enumerate(players)]
    assert [r['D'] for r in rows] == [2,2,2,5,10]
    for r in rows:
        for key in ('dodge','parry','unarmed','blade','tiger_force_hit','tiger_blade_hit'):
            assert isinstance(r[key], int) and r[key] >= 0
    # Deterministic regression fingerprints: catches accidental formula changes.
    assert rows == [
        {'D': 2, 'dodge': 2, 'parry': 2, 'unarmed': 48, 'blade': 5, 'tiger_force_hit': 8, 'tiger_blade_hit': 6},
        {'D': 2, 'dodge': 4, 'parry': 4, 'unarmed': 102, 'blade': 20, 'tiger_force_hit': 12, 'tiger_blade_hit': 27},
        {'D': 2, 'dodge': 6, 'parry': 3, 'unarmed': 143, 'blade': 57, 'tiger_force_hit': 58, 'tiger_blade_hit': 56},
        {'D': 5, 'dodge': 32, 'parry': 20, 'unarmed': 66, 'blade': 44, 'tiger_force_hit': 115, 'tiger_blade_hit': 66},
        {'D': 10, 'dodge': 20, 'parry': 140, 'unarmed': 33, 'blade': 45, 'tiger_force_hit': 15, 'tiger_blade_hit': 39},
    ]
