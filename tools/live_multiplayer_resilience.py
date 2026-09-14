#!/usr/bin/env python3
"""Real-Neolith two-account resilience gate.
Passwords remain in memory only. Exercises canonical tell/save/link-dead reconnect repeatedly,
verifies per-player save files after every save wave, and scans only newly appended debug.log text
for save/mkdir failures. No gameplay data is invented or modified.
"""
import argparse,getpass,hashlib,json,re,socket,sys,threading,time
from pathlib import Path
IAC=255; DO=253; DONT=254; WILL=251; WONT=252; SB=250; SE=240

def strip_telnet(d):
 out=bytearray();i=0
 while i<len(d):
  if d[i]!=IAC: out.append(d[i]);i+=1;continue
  if i+1>=len(d): break
  c=d[i+1]
  if c==IAC: out.append(IAC);i+=2;continue
  if c in (DO,DONT,WILL,WONT): i+=3;continue
  if c==SB:
   j=i+2
   while j+1<len(d) and not(d[j]==IAC and d[j+1]==SE): j+=1
   i=min(len(d),j+2);continue
  i+=2
 return bytes(out)

class Client:
 def __init__(self,h,p,u): self.h=h;self.p=p;self.u=u;self.s=None;self.buf='';self.last_tell_sent=0.0
 def connect(self):
  last=None
  for attempt in range(6):
   try:
    self.s=socket.create_connection((self.h,self.p),timeout=3);self.s.settimeout(.25);return
   except OSError as e:
    last=e
    if attempt<5: time.sleep(1.0)
  raise ConnectionError(f'Neolith {self.h}:{self.p} refused/unavailable after 6 attempts: {last}')
 def send(self,x): self.s.sendall((x+'\r\n').encode('utf-8'))
 def read(self,sec=.7):
  end=time.time()+sec;out=[]
  while time.time()<end:
   try:
    d=self.s.recv(65536)
    if not d: break
    out.append(strip_telnet(d).decode('utf-8','replace'))
   except socket.timeout: pass
  t=''.join(out);self.buf+=t;return t
 def wait(self,pats,sec=15):
  end=time.time()+sec
  while time.time()<end:
   self.read(.25)
   if any(re.search(p,self.buf,re.S) for p in pats): return self.buf
  raise TimeoutError(self.u+' waiting '+str(pats))
 def drain(self,sec=.35):
  self.buf='';return self.read(sec)
 def wait_token(self,token,sec=3.0):
  end=time.time()+sec;out=[]
  while time.time()<end:
   chunk=self.read(.20);out.append(chunk)
   if token in ''.join(out): return ''.join(out),True
  return ''.join(out),False
 def close(self):
  try:
   if self.s:self.s.close()
  except: pass
  self.s=None

def login(c,pw):
 c.buf='';c.connect();c.wait([r'使用者代號',r'您的使用者代號']);c.buf='';c.send(c.u)
 phase=c.wait([r'請輸入密碼',r'使用者代號',r'創造一個新的人物',r'人物儲存檔出了一些問題'],15)
 if '請輸入密碼' not in phase:
  if '創造一個新的人物' in phase: raise RuntimeError(c.u+': account does not exist (server offered character creation)')
  if '人物儲存檔出了一些問題' in phase: raise RuntimeError(c.u+': canonical login save cannot be restored')
  raise RuntimeError(c.u+': login id rejected; project login IDs must be 3-12 lowercase letters or digits')
 c.buf='';c.send(pw)
 out=c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界',r'密碼錯誤'],18)
 if '密碼錯誤' in out: raise RuntimeError(c.u+': bad password')
 c.buf='';c.read(.4);return out

def fsha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def save_paths(mud,u): return [mud/'data/user'/u[0]/(u+'.o'),mud/'data/login'/u[0]/(u+'.o')]
def legal_existing_id(mud,u):
 if not re.fullmatch(r'[a-z0-9]{3,12}',u): return False,'Project login IDs must be 3-12 lowercase letters a-z or digits 0-9.'
 p=mud/'data/login'/u[0]/(u+'.o')
 if not p.exists(): return False,'No canonical login save exists at '+str(p.relative_to(mud))+'. Use an existing character ID.'
 return True,''
def save_ok_text(t): return ('檔案儲存完畢' in t) or ('儲存' in t and '失敗' not in t)

# Canonical /cmds/std/tell.c defines MIN_TELL_INTERVAL as 3 seconds.  The live
# acceptance gate deliberately waits a little longer so it tests multiplayer
# delivery instead of accidentally testing the anti-spam cooldown.
TELL_MIN_INTERVAL=3.0
TELL_SAFETY_MARGIN=.35

def progress(msg):
 print(time.strftime('[%H:%M:%S]'),msg,flush=True)
TELL_FAILURE_TEXTS={
 'cooldown':'你必須休息一下才能再度使用這個指令',
 'missing':'沒有這個人',
 'linkdead':'這個人現在沒辦法聽到你的訊息',
 'ignore_all':'這個人現在不接收任何人的談話',
 'ignored':'對方不想聽你說話',
}

def _clip(t,n=800):
 t=re.sub(r'\x1b\[[0-9;?]*[ -/]*[@-~]','',t or '')
 return t[-n:]

def _pace_tell(c):
 wait=(TELL_MIN_INTERVAL+TELL_SAFETY_MARGIN)-(time.monotonic()-c.last_tell_sent)
 if wait>0: time.sleep(wait)

def tell_once(sender,recipient,target_id,token,wave):
 # Clear old prompts, pace the canonical per-sender tell cooldown, then observe
 # both sockets in one bounded loop. This avoids the old sequential 2.5s + 3.5s
 # waits that made a healthy live run look frozen.
 sender.drain(.12); recipient.drain(.12)
 _pace_tell(sender)
 sender.send('tell '+target_id+' '+token); sender.last_tell_sent=time.monotonic()
 deadline=time.monotonic()+4.25; sender_parts=[]; recipient_parts=[]
 sender_seen=False; recipient_seen=False
 while time.monotonic()<deadline:
  sender_parts.append(sender.read(.10)); recipient_parts.append(recipient.read(.10))
  sender_out=''.join(sender_parts); recipient_out=''.join(recipient_parts)
  sender_seen=sender_seen or token in sender_out
  recipient_seen=recipient_seen or token in recipient_out
  if recipient_seen: break
 sender_out=''.join(sender_parts); recipient_out=''.join(recipient_parts)
 ok=recipient_seen
 reason='delivered' if ok else 'no recipient token observed'
 if not ok:
  combined=sender_out+'\n'+recipient_out
  for key,text in TELL_FAILURE_TEXTS.items():
   if text in combined:
    reason=key;break
 return ok,{'wave':wave,'sender':sender.u,'target':target_id,'token':token,
            'reason':reason,'senderSawToken':sender_seen,'recipientSawToken':recipient_seen,
            'senderOutput':_clip(sender_out),'recipientOutput':_clip(recipient_out)}

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--root',default=str(Path(__file__).resolve().parents[1]));ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');ap.add_argument('--waves',type=int,default=20);ap.add_argument('--reconnect-every',type=int,default=5);ap.add_argument('--report',default='multiplayer_resilience_report.json');a=ap.parse_args()
 root=Path(a.root);mud=root/'source/upstream/mudlib';log=mud/'log/debug.log';log_start=log.stat().st_size if log.exists() else 0
 ua=(a.user_a or input('Existing test user A (3-12 letters/digits): ')).strip().lower();ub=(a.user_b or input('Existing test user B (3-12 letters/digits): ')).strip().lower()
 if not ua or not ub or ua==ub: print('Need two different existing ids.');return 2
 for u in (ua,ub):
  ok,msg=legal_existing_id(mud,u)
  if not ok:
   print('[ACCOUNT CHECK FAILED]',u+':',msg)
   print('No password was requested or sent. Re-run this gate with two existing 3-12 character IDs using lowercase letters/digits.')
   return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ');progress('Credentials entered. Starting two-account live gate...')
 A=Client(a.host,a.port,ua);B=Client(a.host,a.port,ub)
 stats={'version':(ROOT/'VERSION').read_text(encoding='utf-8').strip(),'users':[ua,ub],'waves':max(1,a.waves),'tellPass':0,'tellFail':0,'tellFailures':[],'tellIntervalSeconds':TELL_MIN_INTERVAL,'tellSafetyMarginSeconds':TELL_SAFETY_MARGIN,'savePass':0,'saveFail':0,'fileChecks':0,'fileFailures':[],'reconnectPass':0,'reconnectFail':0,'debugSaveErrors':[],'errors':[],'started':time.strftime('%Y-%m-%dT%H:%M:%S')}
 try:
  errs=[]
  def lg(c,p):
   try: login(c,p)
   except Exception as e: errs.append(str(e))
  ts=[threading.Thread(target=lg,args=(A,pa)),threading.Thread(target=lg,args=(B,pb))]
  progress('LOGIN: connecting both characters...');[t.start() for t in ts];[t.join(40) for t in ts]
  if any(t.is_alive() for t in ts): raise TimeoutError('LOGIN phase exceeded 40 seconds')
  if errs: raise RuntimeError('; '.join(errs))
  progress('LOGIN: PASS for both characters')
  for i in range(1,max(1,a.waves)+1):
   wave_started=time.monotonic();progress(f'WAVE {i}/{max(1,a.waves)}: tell A->B, tell B->A, concurrent save'+(' + reconnect A' if a.reconnect_every>0 and i%a.reconnect_every==0 else ''))
   token=f'RES{i}_{int(time.time()*1000)}'
   got,detail=tell_once(A,B,ub,token,i);stats['tellPass' if got else 'tellFail']+=1
   if not got: stats['tellFailures'].append(detail);progress(f'  tell A->B: FAIL ({detail["reason"]})')
   else: progress('  tell A->B: PASS')
   token2=token+'B'
   got,detail=tell_once(B,A,ua,token2,i);stats['tellPass' if got else 'tellFail']+=1
   if not got: stats['tellFailures'].append(detail);progress(f'  tell B->A: FAIL ({detail["reason"]})')
   else: progress('  tell B->A: PASS')
   outs={};bar=threading.Barrier(2)
   def sv(c,k): bar.wait();c.send('save');outs[k]=c.read(1.6)
   x=threading.Thread(target=sv,args=(A,'a'),daemon=True);y=threading.Thread(target=sv,args=(B,'b'),daemon=True);x.start();y.start();x.join(6);y.join(6)
   if x.is_alive() or y.is_alive(): raise TimeoutError(f'WAVE {i}: concurrent save phase exceeded 6 seconds')
   for k in ('a','b'): stats['savePass' if save_ok_text(outs.get(k,'')) else 'saveFail']+=1
   progress('  concurrent save: '+('PASS' if all(save_ok_text(outs.get(k,'')) for k in ('a','b')) else 'FAIL'))
   time.sleep(.2)
   for u in (ua,ub):
    for p in save_paths(mud,u):
     stats['fileChecks']+=1
     if not(p.exists() and p.stat().st_size>0): stats['fileFailures'].append(str(p.relative_to(mud)))
    for base in ('data/user','data/login'):
     d=mud/base/u[0]
     if d.exists():
      for p in d.glob(u+'.o.tmp*'): stats['fileFailures'].append('orphan:'+str(p.relative_to(mud)))
   if a.reconnect_every>0 and i%a.reconnect_every==0:
    A.close();time.sleep(.7);A=Client(a.host,a.port,ua)
    try:
     progress('  reconnect A: starting...');out=login(A,pa);ok='重新連線' in out;stats['reconnectPass' if ok else 'reconnectFail']+=1;progress('  reconnect A: '+('PASS' if ok else 'FAIL'))
    except Exception as e: stats['reconnectFail']+=1;raise
   progress(f'WAVE {i}/{max(1,a.waves)} complete in {time.monotonic()-wave_started:.1f}s | tell {stats["tellPass"]}P/{stats["tellFail"]}F | save {stats["savePass"]}P/{stats["saveFail"]}F | reconnect {stats["reconnectPass"]}P/{stats["reconnectFail"]}F')
  # final independent hashes prove the two canonical bodies are distinct files, without exposing contents
  stats['finalFiles']={}
  for u in (ua,ub):
   stats['finalFiles'][u]=[]
   for p in save_paths(mud,u):
    if p.exists(): stats['finalFiles'][u].append({'path':str(p.relative_to(mud)),'bytes':p.stat().st_size,'sha256':fsha(p)})
 except Exception as e: stats['errors'].append(str(e))
 finally:
  A.close();B.close()
  if log.exists():
   try:
    with log.open('rb') as f:f.seek(log_start);new=f.read().decode('utf-8','replace')
    bad=[]
    for line in new.splitlines():
     low=line.lower()
     if ('save_object' in low or 'mkdir:' in low) and ('denied' in low or 'error' in low or 'no such file' in low): bad.append(line[-500:])
    stats['debugSaveErrors']=bad[-50:]
   except Exception as e: stats['errors'].append('debug log scan: '+str(e))
  stats['finished']=time.strftime('%Y-%m-%dT%H:%M:%S')
  stats['ok']=not(stats['tellFail'] or stats['saveFail'] or stats['fileFailures'] or stats['reconnectFail'] or stats['debugSaveErrors'] or stats['errors'])
  progress('Live gate finished. Writing report...');text=json.dumps(stats,ensure_ascii=False,indent=2);Path(a.report).write_text(text,encoding='utf-8');print('\n'+text);print('\nReport:',a.report,flush=True)
 return 0 if stats['ok'] else 3
if __name__=='__main__':sys.exit(main())
