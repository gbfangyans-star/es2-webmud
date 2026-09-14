#!/usr/bin/env python3
"""Live Neolith connection-storm/churn gate. No accounts or gameplay data required."""
import argparse,json,socket,threading,time
from pathlib import Path

def one(host,port,timeout,hold,idx):
    s=None; total=0; err=''
    try:
        s=socket.create_connection((host,port),timeout=timeout); s.settimeout(.25)
        end=time.time()+timeout
        while time.time()<end and total==0:
            try:
                d=s.recv(8192)
                if not d: break
                total+=len(d)
            except socket.timeout: pass
        if total and hold: time.sleep(hold)
    except Exception as e: err=str(e)
    finally:
        try:
            if s:s.close()
        except: pass
    return {'client':idx,'ok':total>0,'bytes':total,'error':err}

def wave(host,port,count,timeout,hold):
    rows=[None]*count
    def run(i): rows[i]=one(host,port,timeout,hold,i+1)
    ts=[threading.Thread(target=run,args=(i,)) for i in range(count)]
    for t in ts:t.start()
    for t in ts:t.join()
    return rows

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--root',default=str(Path(__file__).resolve().parents[1]));ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--clients',type=int,default=50);ap.add_argument('--waves',type=int,default=5);ap.add_argument('--timeout',type=float,default=6);ap.add_argument('--hold',type=float,default=.15);ap.add_argument('--report',default='neolith_storm_report.json');a=ap.parse_args()
    a.clients=max(1,min(100,a.clients));a.waves=max(1,min(50,a.waves));root=Path(a.root);log=root/'source/upstream/mudlib/log/debug.log';start=log.stat().st_size if log.exists() else 0
    release=(root/'VERSION').read_text(encoding='utf-8').strip() if (root/'VERSION').exists() else 'unknown'
    rep={'version':release,'host':a.host,'port':a.port,'clientsPerWave':a.clients,'waves':a.waves,'attempted':0,'acceptedWithBanner':0,'failed':[],'debugErrors':[],'started':time.strftime('%Y-%m-%dT%H:%M:%S')}
    for w in range(1,a.waves+1):
        rows=wave(a.host,a.port,a.clients,a.timeout,a.hold);rep['attempted']+=len(rows);rep['acceptedWithBanner']+=sum(1 for r in rows if r['ok'])
        rep['failed'] += [{'wave':w,**r} for r in rows if not r['ok']]
        time.sleep(.25)
    # one final clean connection proves listener still answers after churn
    final=one(a.host,a.port,a.timeout,0,0);rep['postStormProbe']=final
    if log.exists():
        try:
            with log.open('rb') as f:f.seek(start);new=f.read().decode('utf-8','replace')
            needles=('too many open files','out of memory','fatal','assertion failed','access violation')
            rep['debugErrors']=[ln[-500:] for ln in new.splitlines() if any(n in ln.lower() for n in needles)][-50:]
        except Exception as e:rep['debugErrors']=['log scan failed: '+str(e)]
    rep['finished']=time.strftime('%Y-%m-%dT%H:%M:%S');rep['ok']=not rep['failed'] and final['ok'] and not rep['debugErrors']
    Path(a.report).write_text(json.dumps(rep,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(rep,ensure_ascii=False,indent=2));print('\nReport:',a.report)
    return 0 if rep['ok'] else 3
if __name__=='__main__':raise SystemExit(main())
