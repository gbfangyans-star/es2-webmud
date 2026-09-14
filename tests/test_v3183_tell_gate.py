from pathlib import Path
import importlib.util
R=Path(__file__).resolve().parents[1]

def test_version():
 assert (R/'VERSION').read_text().strip().startswith('3.')

def test_canonical_tell_interval_is_three_seconds():
 s=(R/'source/upstream/mudlib/cmds/std/tell.c').read_text(encoding='utf-8')
 assert '#define MIN_TELL_INTERVAL\t3' in s or '#define MIN_TELL_INTERVAL    3' in s

def test_live_gate_paces_and_diagnoses_tell():
 s=(R/'tools/live_multiplayer_resilience.py').read_text(encoding='utf-8')
 for x in ['TELL_MIN_INTERVAL=3.0','TELL_SAFETY_MARGIN=.35','_pace_tell(sender)','deadline=time.monotonic()+4.25',"'tellFailures':[]","'cooldown':'你必須休息一下才能再度使用這個指令'"]:
  assert x in s

def test_master_embeds_live_summary():
 s=(R/'tools/multiplayer_master_gate.py').read_text(encoding='utf-8')
 assert "live_stage['summary']" in s
 assert "live_stage['tellFailureSample']" in s
