import importlib.util,json,subprocess,sys,tempfile
from pathlib import Path
ROOT=Path(__file__).parents[1]
spec=importlib.util.spec_from_file_location("idx",ROOT/"tools/index_es2.py");idx=importlib.util.module_from_spec(spec);spec.loader.exec_module(idx)
src=(ROOT/"tests/fixture/mudlib/d/snow/npc/vendor_test.c").read_text(encoding="utf-8")
rec=idx.extract(ROOT/"tests/fixture/mudlib/d/snow/npc/vendor_test.c",ROOT/"tests/fixture/mudlib")
assert rec["type"]=="npc"
assert rec["merchandise"][0]["stock"]==3
assert rec["skills"][0]=={"skill":"unarmed","level":20}
assert rec["skill_maps"][0]["mapped_to"]=="test-art"
assert rec["callouts"][0]["delay"]==2
assert any(x.get("verb")=="talk" for x in rec["actions"])
door=(ROOT/"tests/fixture/mudlib/d/snow/doorroom.c").read_text(encoding="utf-8")
assert idx.parse_doors(door)[0]["direction"]=="west"
print("v0.7 parser tests passed")
