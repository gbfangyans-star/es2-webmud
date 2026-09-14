#!/usr/bin/env python3
"""Concurrent live-save verification against canonical /data login/user shards."""
import argparse,getpass,hashlib,re,socket,sys,threading,time
from pathlib import Path
IAC=255

def clean(d):
 out=bytearray();i=0
 while i<len(d):
  if d[i]!=IAC:out.append(d[i]);i+=1;continue
  if i+1>=len(d):break
  c=d[i+1]
  if c in (251,252,253,254):i+=3;continue
  if c==250:
   j=i+2
   while j+1<len(d) and not(d[j]==255 and d[j+1]==240):j+=1
   i=min(len(d),j+2);continue
  i+=2
 return bytes(out)
class C:
 def __init__(self,h,p):self.h=h;self.p=p;self.s=None;self.b=''
 def conn(self):self.s=socket.create_connection((self.h,self.p),timeout=8);self.s.settimeout(.25)
 def send(self,x):self.s.sendall((x+'\r\n').encode())
 def read(self,sec=.8):
  end=time.time()+sec;z=[]
  while time.time()<end:
   try:z.append(clean(self.s.recv(65536)).decode('utf8','replace'))
   except socket.timeout:pass
  t=''.join(z);self.b+=t;return t
 def wait(self,p,sec=12):
  end=time.time()+sec
  while time.time()<end:
   self.read(.25)
   if any(re.search(x,self.b,re.S) for x in p):return self.b
  raise TimeoutError(str(p))
 def close(self):
  try:self.s.close()
  except:pass
def login(c,u,p):
 c.conn();c.wait([r'使用者代號']);c.send(u);c.wait([r'請輸入密碼']);c.send(p);c.wait([r'目前權限',r'重新連線'],15);c.b='';c.read(.5)
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--root',default=str(Path(__file__).resolve().parents[1]));ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');a=ap.parse_args();root=Path(a.root);mud=root/'source/upstream/mudlib';ua=a.user_a or input('Existing test user A: ').strip().lower();ub=a.user_b or input('Existing test user B: ').strip().lower()
 if not ua or not ub or ua==ub:return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ');A=C(a.host,a.port);B=C(a.host,a.port)
 try:
  x=threading.Thread(target=login,args=(A,ua,pa));y=threading.Thread(target=login,args=(B,ub,pb));x.start();y.start();x.join();y.join();outs={}
  def save(c,k):c.send('save');outs[k]=c.read(2)
  x=threading.Thread(target=save,args=(A,'a'));y=threading.Thread(target=save,args=(B,'b'));x.start();y.start();x.join();y.join();time.sleep(.5)
  ok=True
  for u in (ua,ub):
   paths=[mud/'data/user'/u[0]/(u+'.o'),mud/'data/login'/u[0]/(u+'.o')]
   for p in paths:
    good=p.exists() and p.stat().st_size>0
    print(('[PASS] ' if good else '[FAIL] ')+str(p.relative_to(mud))+(f' bytes={p.stat().st_size} sha256={sha(p)[:16]}...' if good else ' missing/empty'));ok&=good
   tmps=list((mud/'data/user'/u[0]).glob(u+'.o.tmp*'))+list((mud/'data/login'/u[0]).glob(u+'.o.tmp*'))
   good=not tmps;print(('[PASS] ' if good else '[FAIL] ')+u+' no orphan save temp files');ok&=good
  return 0 if ok else 3
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':sys.exit(main())
