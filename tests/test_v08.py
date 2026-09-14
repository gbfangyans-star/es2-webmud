import importlib.util
from pathlib import Path
R=Path(__file__).parents[1]
spec=importlib.util.spec_from_file_location("idx",R/"tools/index_es2.py");m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
for fn,slot in [("cloth.c","cloth"),("fur_hat.c","head_eq")]:
    p=R/"tests/fixture/mudlib/obj/armor"/fn
    rec=m.extract(p,R/"tests/fixture/mudlib")
    assert rec["type"]=="item"
    assert rec["wear_as"]==slot
    assert rec["armor_apply"][0]["slot"]==slot
    assert rec["armor_apply"][0]["values"]["armor"]==1
    assert slot in rec["setup_kinds"]
print("v0.8 equipment parser tests passed")
