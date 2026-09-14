#!/usr/bin/env python3
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / "source" / "upstream" / "mudlib"

def text_files():
    for p in MUD.rglob('*'):
        if 'custom' in p.relative_to(MUD).parts:
            continue
        if p.is_file() and p.suffix in {'.c','.h'}:
            yield p

def contains(term):
    for p in text_files():
        try:
            if term in p.read_text(encoding='utf-8', errors='ignore'):
                return True, p
        except OSError:
            pass
    return False, None

checks = []
nec, np = contains('necromancy')
checks.append(('current canonical has no necromancy dependency', not nec))
blk, bp = contains('black_cloth')
checks.append(('current canonical has no black_cloth dependency', not blk))
dust = MUD / 'obj' / 'dust.c'
checks.append(('current canonical obj/dust.c exists', dust.is_file()))
for name, result in checks:
    print(('PASS' if result else 'FAIL') + ' - ' + name)
if not all(r for _,r in checks):
    raise SystemExit(1)
print(f'PASS {sum(r for _,r in checks)}/{len(checks)} checks')
