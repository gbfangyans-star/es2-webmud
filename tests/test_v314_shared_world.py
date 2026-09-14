from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def test_version(): assert (ROOT/'VERSION').read_text().strip().startswith('3.')
def test_gate_files():
 assert (ROOT/'CHECK_MULTIPLAYER_SHARED_WORLD.bat').exists()
 s=(ROOT/'tools/live_multiplayer_sharedworld.py').read_text(encoding='utf-8')
 assert 'get '+"'" in s and "look '+npc" in s and "fight '+npc" not in s and "send('kill" not in s
def test_audit_scope():
 s=(ROOT/'tools/audit_multiplayer_v314.py').read_text(encoding='utf-8')
 for x in ['item->move(who)','obj->move(me)','last_damage_giver()','wake_guard(this_object())']: assert x in s
