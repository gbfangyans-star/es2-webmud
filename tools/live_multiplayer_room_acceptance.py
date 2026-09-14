#!/usr/bin/env python3
"""Two-real-account live Neolith room/team/follow/guard acceptance.
Passwords stay in memory. Uses only canonical ES2 commands and does not create gameplay rules.
"""
import argparse,getpass,re,socket,sys,threading,time
IAC=255;DO=253;DONT=254;WILL=251;WONT=252;SB=250;SE=240

def strip_telnet(d):
 out=bytearray();i=0
 while i<len(d):
  if d[i]!=IAC:out.append(d[i]);i+=1;continue
  if i+1>=len(d):break
  c=d[i+1]
  if c==IAC:out.append(IAC);i+=2;continue
  if c in (DO,DONT,WILL,WONT):i+=3;continue
  if c==SB:
   j=i+2
   while j+1<len(d) and not(d[j]==IAC and d[j+1]==SE):j+=1
   i=min(len(d),j+2);continue
  i+=2
 return bytes(out)
class C:
 def __init__(self,h,p,n):self.h=h;self.p=p;self.n=n;self.s=None;self.b=''
 def conn(self):self.s=socket.create_connection((self.h,self.p),timeout=8);self.s.settimeout(.25)
 def send(self,x):self.s.sendall((x+'\r\n').encode('utf-8'))
 def read(self,sec=.8):
  end=time.time()+sec;z=[]
  while time.time()<end:
   try:
    d=self.s.recv(65536)
    if not d:break
    z.append(strip_telnet(d).decode('utf-8','replace'))
   except socket.timeout:pass
  t=''.join(z);self.b+=t;return t
 def wait(self,pats,sec=12):
  end=time.time()+sec
  while time.time()<end:
   self.read(.25)
   if any(re.search(p,self.b,re.S) for p in pats):return self.b
  raise TimeoutError(self.n+' waiting '+str(pats))
 def clear(self):self.b='';self.read(.25);self.b=''
 def close(self):
  try:
   if self.s:self.s.close()
  except:pass

def login(c,u,pw):
 c.conn();c.wait([r'使用者代號',r'您的使用者代號']);c.send(u);c.wait([r'請輸入密碼']);c.send(pw)
 out=c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界'],15)
 if '密碼錯誤' in out:raise RuntimeError(u+': bad password')
 c.clear()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');a=ap.parse_args()
 ua=a.user_a or input('Existing user A: ').strip().lower();ub=a.user_b or input('Existing user B: ').strip().lower()
 if not ua or not ub or ua==ub:print('Need two different existing ids.');return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ');A=C(a.host,a.port,ua);B=C(a.host,a.port,ub);R=[]
 try:
  errs=[]
  def lg(c,u,p):
   try:login(c,u,p)
   except Exception as e:errs.append(str(e))
  x=threading.Thread(target=lg,args=(A,ua,pa));y=threading.Thread(target=lg,args=(B,ub,pb));x.start();y.start();x.join();y.join()
  if errs:raise RuntimeError('; '.join(errs))
  R.append(('two real accounts logged in',True))
  # The tool never teleports or invents a test room. Both existing characters must already be in the same room.
  A.send('look');B.send('look');al=A.read(1.2);bl=B.read(1.2)
  print('\n--- USER A LOOK ---\n'+al[-1600:]);print('\n--- USER B LOOK ---\n'+bl[-1600:])
  A.clear();B.clear();token='ROOM'+str(int(time.time()));A.send('say '+token);bout=B.read(1.5);R.append(('same-room say A -> B',token in bout))
  # Canonical two-party team handshake, then team-scoped chat.
  A.clear();B.clear();A.send('team with '+ub);B.read(1);B.send('team with '+ua);A.read(1);B.read(1);A.send('team');tout=A.read(1);R.append(('team handshake/list',('隊伍' in tout) and (ub.lower() in tout.lower())))
  A.clear();B.clear();tt='TEAM'+str(int(time.time()));A.send('team talk '+tt);bt=B.read(1.5);R.append(('team talk A -> B',tt in bt))
  # Follow uses a real exit chosen by the operator from the LOOK output above.
  move=input('Enter one valid exit direction shown above for the follow test (or blank to skip): ').strip().lower()
  if move:
   B.clear();B.send('follow '+ua);B.read(1);A.clear();B.clear();A.send('look');before=A.read(1);A.clear();B.clear();A.send('go '+move);A.read(1.2);B.read(1.2);B.send('look');after=B.read(1.5);R.append(('follow movement through chosen canonical exit',bool(after.strip()) and after!=before))
  else:R.append(('follow movement through chosen canonical exit',False))
  # Guard contract: level restrictions may reject low-level test chars; report as CHECK, not hard failure.
  A.clear();B.clear();A.send('guard '+ub);g=A.read(1);guard_ok=('Ok.' in g or '保護' in g) and ('長大點' not in g);R.append(('guard relation (requires canonical level >=5)',guard_ok))
  # Clean up team/follow/guard state without quitting/saving locations.
  for c in (A,B):c.send('guard cancel');c.send('follow none');c.send('team dismiss');c.read(.5)
  print('\nLIVE ROOM/TEAM/FOLLOW ACCEPTANCE')
  for n,ok in R:print(('[PASS] ' if ok else '[CHECK] ')+n)
  hard=[x for x in R if not x[0].startswith('guard relation')]
  return 0 if all(x[1] for x in hard) else 3
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':sys.exit(main())
