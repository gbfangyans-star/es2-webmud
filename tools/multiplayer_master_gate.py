#!/usr/bin/env python3
"""Unified ES2 multiplayer acceptance gate for the real Windows/Neolith host."""
import argparse,json,socket,subprocess,sys,time,urllib.request
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
VERSION=(ROOT/'VERSION').read_text(encoding='utf-8').strip()

def run(name,cmd,cwd=ROOT):
    print('\n'+'='*68);print(name);print('='*68);started=time.time()
    try:
        rc=subprocess.call(cmd,cwd=str(cwd))
        return {'name':name,'status':'PASS' if rc==0 else 'FAIL','exitCode':rc,'seconds':round(time.time()-started,2)}
    except Exception as e:
        print('[FAIL]',e);return {'name':name,'status':'FAIL','exitCode':99,'seconds':round(time.time()-started,2),'error':str(e)}

def port_open(host,port,timeout=2):
    try:
        with socket.create_connection((host,port),timeout=timeout): return True
    except OSError:return False

def bridge_identity(port=8080):
    try:
        with urllib.request.urlopen(f'http://127.0.0.1:{port}/api/version',timeout=2) as r: data=json.loads(r.read().decode('utf-8'))
        expected=str(ROOT.resolve()).lower().replace('\\','/')
        actual=str(data.get('projectRoot','')).lower().replace('\\','/')
        ok=data.get('version')==VERSION and actual==expected
        return ok,data,None if ok else f"Expected v{VERSION} at {ROOT}; found v{data.get('version')} at {data.get('projectRoot')}"
    except Exception as e:return False,None,str(e)

def listener_stable(host,port,checks=5,delay=.6):
    rows=[]
    for _ in range(checks): rows.append(port_open(host,port,1.5));time.sleep(delay)
    return all(rows),rows

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--web-port',type=int,default=8080);ap.add_argument('--skip-live',action='store_true');ap.add_argument('--storm-clients',type=int,default=50);ap.add_argument('--storm-waves',type=int,default=5);ap.add_argument('--resilience-waves',type=int,default=20);ap.add_argument('--reconnect-every',type=int,default=5);ap.add_argument('--report',default='multiplayer_master_report.json');a=ap.parse_args()
    py=sys.executable;node='node';stages=[]
    audits=['audit_multiplayer_gameplay.py','audit_multiplayer_deep.py','audit_multiplayer_v39.py','audit_multiplayer_v310.py','audit_multiplayer_v311.py','audit_multiplayer_v313.py','audit_multiplayer_v314.py','audit_multiplayer_v315.py','audit_multiplayer_v316.py','audit_multiplayer_v317.py']
    for f in audits:stages.append(run('Canonical audit: '+f,[py,str(ROOT/'tools'/f)]))
    stages.append(run('WebMUD per-session bridge structural audit',[node,str(ROOT/'tools/audit_multiplayer_bridge.mjs'),str(ROOT/'server/index.js')]))
    stages.append(run('8-session bridge isolation',[node,str(ROOT/'tests/test_multiplayer_isolation_v34.mjs')]))
    stages.append(run('500-session bridge endurance',[node,str(ROOT/'tests/test_multiplayer_endurance_v317.mjs')]))
    if not a.skip_live:
        ident_ok,ident,ident_err=bridge_identity(a.web_port)
        stages.append({'name':'Running WebMUD version identity','status':'PASS' if ident_ok else 'FAIL','exitCode':0 if ident_ok else 96,'identity':ident,'error':ident_err} if not ident_ok else {'name':'Running WebMUD version identity','status':'PASS','exitCode':0,'identity':ident})
        if not ident_ok:
            print('\n[STOP] The server on port',a.web_port,'is not this project version. Close old ES2 server windows and run START_ES2.bat from this folder.')
        elif not port_open(a.host,a.port):
            stages.append({'name':'Real Neolith TCP listener','status':'FAIL','exitCode':98,'error':f'{a.host}:{a.port} is not accepting connections. Keep the Neolith window open.'})
        else:
            stages.append({'name':'Real Neolith TCP listener','status':'PASS','exitCode':0})
            print('\nAuthenticated functional gate FIRST. Heavy connection storm runs only after real-player functionality.')
            print('Passwords are hidden and remain memory-only.')
            live_stage=run('Two-character tell/save/link-dead/reconnect resilience',[py,str(ROOT/'tools/live_multiplayer_resilience.py'),'--root',str(ROOT),'--host',a.host,'--port',str(a.port),'--waves',str(max(1,a.resilience_waves)),'--reconnect-every',str(max(1,a.reconnect_every)),'--report','multiplayer_resilience_report.json'])
            try:
                live=json.loads((ROOT/'multiplayer_resilience_report.json').read_text(encoding='utf-8'))
                live_stage['summary']={k:live.get(k) for k in ('tellPass','tellFail','savePass','saveFail','fileChecks','reconnectPass','reconnectFail','debugSaveErrors','errors')}
                if live.get('tellFailures'):live_stage['tellFailureSample']=live['tellFailures'][:4]
            except Exception as e:live_stage['reportReadError']=str(e)
            stages.append(live_stage)
            if port_open(a.host,a.port):
                storm=run('Real Neolith connection storm (runs last)',[py,str(ROOT/'tools/live_neolith_storm.py'),'--root',str(ROOT),'--host',a.host,'--port',str(a.port),'--clients',str(max(1,a.storm_clients)),'--waves',str(max(1,a.storm_waves)),'--report','neolith_storm_report.json']);stages.append(storm)
                time.sleep(2.0);stable,probes=listener_stable(a.host,a.port)
                stages.append({'name':'Post-storm Neolith stability','status':'PASS' if stable else 'FAIL','exitCode':0 if stable else 97,'probes':probes,'error':None if stable else 'Neolith did not remain continuously reachable after storm.'})
            else:
                stages.append({'name':'Pre-storm Neolith TCP listener','status':'FAIL','exitCode':97,'error':'Neolith stopped accepting connections during authenticated functional testing; storm skipped.'})
    hard_fail=any(s['status']=='FAIL' for s in stages)
    assisted=[
      {'gate':'same-room say/team/follow/guard','launcher':'CHECK_MULTIPLAYER_ROOM.bat','status':'ASSISTED','note':'say/team/follow already have prior live evidence; guard remains conditional on canonical level'},
      {'gate':'ground-item single-owner contention','launcher':'CHECK_MULTIPLAYER_SHARED_WORLD.bat','status':'ASSISTED','note':'requires a real visible ground item; no spawning'},
      {'gate':'mutual player fight in combat-allowed room','launcher':'CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat','status':'ASSISTED','note':'preferred low-risk combat gate; never kill'},
      {'gate':'shared real NPC combat','launcher':'CHECK_MULTIPLAYER_COMBAT_LIVE.bat','status':'ASSISTED-RISKY','note':'canonical non-civilized NPC may answer fight with kill_ob(); not required for low-risk certification'},
      {'gate':'death/corpse/revival','launcher':'CHECK_MULTIPLAYER_DEATH.bat','status':'WITHHELD-DESTRUCTIVE','note':'static only until an explicitly approved disposable scenario exists'},
      {'gate':'server restart persistence','launcher':'CHECK_RESTART_BEFORE.bat -> restart Neolith -> CHECK_RESTART_AFTER.bat','status':'ASSISTED','note':'both characters must be offline before BEFORE snapshot'}
    ]
    report={'version':VERSION,'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'mode':'static+bridge' if a.skip_live else 'full-live','ok':not hard_fail,'stages':stages,'operatorAssistedRemaining':assisted,'note':'Authenticated functionality runs before destructive/heavy stress. PASS proves only executed stages.'}
    (ROOT/a.report).write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
    print('\n'+'='*68);print('MULTIPLAYER MASTER RESULT:','PASS' if report['ok'] else 'FAIL');print('Report:',ROOT/a.report)
    return 0 if report['ok'] else 3
if __name__=='__main__':raise SystemExit(main())
