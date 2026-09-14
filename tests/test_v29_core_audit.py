from pathlib import Path
import tempfile,json,runpy,sys
ROOT=Path(__file__).parents[1]
critical={
 '/obj/login':'runtime','/obj/user':'runtime','/std/char':'skill',
 '/feature/char/attack':'feature','/feature/char/combat':'feature',
 '/feature/char/skill':'feature','/feature/char/condition':'feature',
 '/feature/statistic':'feature',
 '/adm/daemons/logind':'daemon','/adm/daemons/enterd':'daemon',
 '/adm/daemons/combatd':'daemon','/adm/daemons/chard':'daemon'
}
with tempfile.TemporaryDirectory() as td:
    d=Path(td)
    rows=[{'path':p,'type':t,'sha256':'a'*64} for p,t in critical.items()]
    (d/'all.json').write_text(json.dumps(rows),encoding='utf-8')
    old=sys.argv[:]
    try:
        sys.argv=[str(ROOT/'tools/core_audit.py'),str(d)]
        try:
            runpy.run_path(str(ROOT/'tools/core_audit.py'),run_name='__main__')
            code=0
        except SystemExit as e:
            code=e.code or 0
    finally:
        sys.argv=old
    assert code==0
    report=json.loads((d/'core_audit.json').read_text(encoding='utf-8'))
    assert report['ok'] is True
    assert report['checks']['char_statistic']['path']=='/feature/statistic'
    assert report['checks']['char_statistic']['present'] is True
print('v2.9 real canonical statistic path regression passed')
