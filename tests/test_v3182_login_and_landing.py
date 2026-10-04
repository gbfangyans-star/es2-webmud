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

def test_login_screen_lines():
 s=(R/'source/upstream/mudlib/adm/daemons/logind.c').read_text(encoding='utf-8')
 assert '現在時間 %s, 東方故事Ⅱ已經執行了%s。' in s
 assert '從 %s 以來累計上線人次：%d 人次。' in s
 assert '如果您是第一次使用，請輸入您喜歡的使用者代號以註冊角色' in s
 assert 'write ("您的使用者代號：");' in s
