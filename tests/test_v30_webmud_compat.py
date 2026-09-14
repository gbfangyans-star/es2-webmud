from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
logind=(ROOT/'source/upstream/mudlib/adm/daemons/logind.c').read_text(encoding='utf-8')
cursor=(ROOT/'source/upstream/mudlib/adm/simul_efun/cursor.c').read_text(encoding='utf-8')
security=(ROOT/'source/upstream/mudlib/adm/daemons/securityd.c').read_text(encoding='utf-8')
user=(ROOT/'source/upstream/mudlib/obj/user.c').read_text(encoding='utf-8')
index=(ROOT/'web/index.html').read_text(encoding='utf-8')

inputc=(ROOT/'source/upstream/mudlib/feature/user/input.c').read_text(encoding='utf-8')
assert '請輸入選項數字' in inputc
assert 'get_char (' not in logind
assert 'sscanf (input, "%d", choice)' in cursor
assert 'path[0]=="data"' in security
assert 'path[1]=="user" || path[1]=="login" || path[1]=="mail"' in security
assert 'path[2]==euid[0..0]' in security
assert 'save();' in user and 'my_link->save();' in user
assert 'charControls' not in index
for d in ['user','login','mail']:
    assert (ROOT/f'source/upstream/mudlib/data/{d}/.keep').exists()
assert (ROOT/'START_ES2.bat').exists()
print('v3.0 WebMUD compatibility contract passed')
