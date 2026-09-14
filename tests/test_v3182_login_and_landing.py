from pathlib import Path
import importlib.util,re
R=Path(__file__).resolve().parents[1]

def loadmod():
 p=R/'tools/live_multiplayer_resilience.py';spec=importlib.util.spec_from_file_location('res',p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

def test_version(): assert (R/'VERSION').read_text().strip().startswith('3.')

def test_resilience_accepts_digit_ids_when_save_exists(tmp_path):
 m=loadmod(); p=tmp_path/'data/login/t';p.mkdir(parents=True);(p/'test01.o').write_text('x')
 ok,msg=m.legal_existing_id(tmp_path,'test01');assert ok and msg==''

def test_resilience_rejects_punctuation(tmp_path):
 m=loadmod();ok,msg=m.legal_existing_id(tmp_path,'test-1');assert not ok and 'letters a-z or digits 0-9' in msg

def test_logind_allows_lowercase_letters_and_digits():
 s=(R/'source/upstream/mudlib/adm/daemons/logind.c').read_text(encoding='utf-8')
 assert "id[i]>='0'" in s and "id[i]<='9'" in s
 assert '英文字母或 0 到 9 的數字' in s

def test_landing_click_target_matches_baked_button():
 s=(R/'web/styles.css').read_text(encoding='utf-8')
 assert 'aspect-ratio:1312/1199' in s
 m=re.search(r'\.landing-enter-target\{[^}]*left:([0-9.]+)%;top:([0-9.]+)%[^}]*width:([0-9.]+)%;height:([0-9.]+)%',s)
 assert m
 left,top,width,height=map(float,m.groups())
 assert 48.5<left<50.5 and 63.5<top<66.0 and width>=29 and height>=8
