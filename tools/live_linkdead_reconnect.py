#!/usr/bin/env python3
"""Two-account live Neolith resilience test: login, tell, abrupt link loss, reconnect, tell again, save.
Passwords use getpass and are never persisted. Requires two existing test accounts.
"""
import argparse,getpass,re,socket,sys,time
IAC=255; DO=253; DONT=254; WILL=251; WONT=252; SB=250; SE=240
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
 def connect(self):self.s=socket.create_connection((self.h,self.p),timeout=8);self.s.settimeout(.3)
 def send(self,x):self.s.sendall((x+'\r\n').encode())
 def drain(self,sec=.8):
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
   self.drain(.3)
   if any(re.search(p,self.buf,re.S) for p in pats):return self.buf
  raise TimeoutError(self.n+' waiting '+str(pats))
 def close(self):
  try:self.s.close()
  except:pass
  self.s=None
def login(c,u,pw):
 c.connect();c.wait([r'使用者代號',r'您的使用者代號']);c.send(u);c.wait([r'請輸入密碼']);c.send(pw);return c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界'],15)
def main():
 a=argparse.ArgumentParser();a.add_argument('--host',default='127.0.0.1');a.add_argument('--port',type=int,default=4000);a.add_argument('--user-a');a.add_argument('--user-b');q=a.parse_args();ua=q.user_a or input('Test user A id: ').strip().lower();ub=q.user_b or input('Test user B id: ').strip().lower()
 if not ua or not ub or ua==ub:print('Need two different existing ids.');return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ');A=C(q.host,q.port,ua);B=C(q.host,q.port,ub);res=[]
 try:
  login(A,ua,pa);login(B,ub,pb);res.append(('two live logins',True));tok='PRE'+str(int(time.time()));A.send(f'tell {ub} {tok}');res.append(('tell before disconnect',tok in B.drain(2)))
  A.close();time.sleep(1.5);A=C(q.host,q.port,ua);out=login(A,ua,pa);res.append(('link-dead reconnect path',('重新連線' in out)))
  time.sleep(3.2);tok='POST'+str(int(time.time()));A.send(f'tell {ub} {tok}');res.append(('tell after reconnect',tok in B.drain(2)))
  A.send('save');sa=A.drain(2);B.send('save');sb=B.drain(2);ok=lambda x:('儲存' in x);res.append(('both save after reconnect',ok(sa) and ok(sb)))
  print('\nLIVE LINK-DEAD / RECONNECT');[print(('[PASS] ' if ok else '[CHECK] ')+n) for n,ok in res];return 0 if all(ok for _,ok in res) else 3
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':sys.exit(main())
