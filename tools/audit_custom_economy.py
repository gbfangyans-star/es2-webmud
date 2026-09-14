from pathlib import Path

ROOT = Path(__file__).resolve().parents[1] / "source" / "upstream" / "mudlib"
checks = []

for money in ("gold", "silver", "coin"):
    text = (ROOT / "obj" / "money" / f"{money}.c").read_text()
    checks.append((f"{money} weightless", 'set("base_weight", 0)' in text))

finance = (ROOT / "feature" / "char" / "finance.c").read_text()
checks += [
    ("finance total-value payment", "query_carried_money_value" in finance),
    ("finance exact change", "set_carried_money_value(total - amount)" in finance),
    ("legacy change-required result retired", "return 2;" not in finance),
]

failed = [name for name, ok in checks if not ok]
for name, ok in checks:
    print(("PASS" if ok else "FAIL") + ": " + name)
if failed:
    raise SystemExit(1)
print("CUSTOM ECONOMY AUDIT: PASS")
