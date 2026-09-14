#!/usr/bin/env python3
"""Live two-account Neolith soak test. Passwords stay in memory only.
Exercises canonical login/tell/who/hp/save and periodic abrupt reconnects.
Writes a password-free JSON report when --report is supplied.
"""
import argparse,getpass,json,re,socket,sys,threading,time
from pathlib import Path
IAC=255;DO=253;DONT=254;WILL=251;WONT=252;SB=250;SE=240

def strip_telnet(d):
 o=bytearray();i=0
 while i<len(d):
  if d[i]!=IAC:o.append(d[i]);i+=1;continue
  if i+1>=len(d):break
  c=d[i+1]
  if c==IAC:o.append(IAC);i+=2;continue
  if c in (DO,DONT,WILL,WONT):i+=3;continue
  if c==SB:
   j=i+2
   while j+1<len(d) and not(d[j]==IAC and d[j+1]==SE):j+=1
   i=min(len(d),j+2);continue
  i+=2
 return bytes(o)
class C:
 def __init__(self,h,p,n):self.h=h;self.p=p;self.n=n;self.s=None;self.buf=''
 def connect(self):self.s=socket.create_connection((self.h,self.p),timeout=8);self.s.settimeout(.25)
 def send(self,x):self.s.sendall((x+'\r\n').encode('utf-8'))
 def drain(self,sec=.7):
  end=time.time()+sec;z=[]
  while time.time()<end:
   try:
    d=self.s.recv(65536)
    if not d:break
    z.append(strip_telnet(d).decode('utf-8','replace'))
   except socket.timeout:pass
  t=''.join(z);self.buf+=t;return t
 def wait(self,pats,sec=12):
  end=time.time()+sec
  while time.time()<end:
   self.drain(.25)
   if any(re.search(p,self.buf,re.S) for p in pats):return self.buf
  raise TimeoutError(self.n+' waiting '+str(pats))
 def close(self):
  try:
   if self.s:self.s.close()
  except:pass
  self.s=None

def login(c,u,pw):
 c.buf='';c.connect();c.wait([r'使用者代號',r'您的使用者代號']);c.send(u);c.wait([r'請輸入密碼']);c.send(pw)
 out=c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界'],15)
 if '密碼錯誤' in out:raise RuntimeError(u+': bad password')
 c.buf='';c.drain(.6);return out

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');ap.add_argument('--minutes',type=float,default=10);ap.add_argument('--interval',type=float,default=5);ap.add_argument('--reconnect-every',type=int,default=12);ap.add_argument('--report')
 a=ap.parse_args();ua=a.user_a or input('Existing test user A: ').strip().lower();ub=a.user_b or input('Existing test user B: ').strip().lower()
 if not ua or not ub or ua==ub:print('Need two different existing ids.');return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ')
 A=C(a.host,a.port,ua);B=C(a.host,a.port,ub);stats={'version':'3.13.0','users':[ua,ub],'started':time.strftime('%Y-%m-%dT%H:%M:%S'),'iterations':0,'tellPass':0,'tellFail':0,'savePass':0,'saveFail':0,'reconnectPass':0,'reconnectFail':0,'errors':[]}
 try:
  ta=threading.Thread(target=login,args=(A,ua,pa));tb=threading.Thread(target=login,args=(B,ub,pb));ta.start();tb.start();ta.join();tb.join()
  end=time.time()+max(30,a.minutes*60);i=0
  while time.time()<end:
   i+=1;stats['iterations']=i;token=f'SOAK{i}_{int(time.time())}'
   A.send(f'tell {ub} {token}');got=token in B.drain(1.4);stats['tellPass' if got else 'tellFail']+=1
   time.sleep(.2);token2=token+'R';B.send(f'tell {ua} {token2}');got=token2 in A.drain(1.4);stats['tellPass' if got else 'tellFail']+=1
   A.send('hp');B.send('hp');A.drain(.5);B.drain(.5)
   if i%3==0:
    outs={}
    def sv(c,k):c.send('save');outs[k]=c.drain(1.3)
    x=threading.Thread(target=sv,args=(A,'a'));y=threading.Thread(target=sv,args=(B,'b'));x.start();y.start();x.join();y.join()
    ok=lambda t:'儲存' in t
    for k in ('a','b'):stats['savePass' if ok(outs.get(k,'')) else 'saveFail']+=1
   if a.reconnect_every>0 and i%a.reconnect_every==0:
    A.close();time.sleep(.8);A=C(a.host,a.port,ua)
    try:
     out=login(A,ua,pa);ok='重新連線' in out;stats['reconnectPass' if ok else 'reconnectFail']+=1
    except Exception as e:stats['reconnectFail']+=1;stats['errors'].append(str(e));raise
   time.sleep(max(.2,a.interval))
 except KeyboardInterrupt:stats['errors'].append('stopped by operator')
 except Exception as e:stats['errors'].append(str(e))
 finally:
  A.close();B.close();stats['finished']=time.strftime('%Y-%m-%dT%H:%M:%S');stats['ok']=stats['tellFail']==0 and stats['reconnectFail']==0 and not [x for x in stats['errors'] if x!='stopped by operator']
  text=json.dumps(stats,ensure_ascii=False,indent=2);print('\n'+text)
  if a.report:Path(a.report).write_text(text,encoding='utf-8')
 return 0 if stats['ok'] else 3
if __name__=='__main__':sys.exit(main())
