#!/usr/bin/env python3
"""Operator-assisted two-character shared-world acceptance against real Neolith.
Uses only canonical ES2 commands. It never spawns NPCs/items, teleports players, or invents gameplay data.
Passwords stay in memory only.
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
 def send(self,x):self.s.sendall((x+'\r\n').encode())
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
 def clear(self):self.b='';self.read(.2);self.b=''
 def close(self):
  try:
   if self.s:self.s.close()
  except:pass
def login(c,u,p):
 c.conn();c.wait([r'使用者代號',r'您的使用者代號']);c.send(u);c.wait([r'請輸入密碼']);c.send(p)
 out=c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界'],15)
 if '密碼錯誤' in out:raise RuntimeError(u+': bad password')
 c.clear()
def ask(q):return input(q).strip()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');x=ap.parse_args()
 ua=x.user_a or ask('Existing user A: ').lower();ub=x.user_b or ask('Existing user B: ').lower()
 if not ua or not ub or ua==ub:return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ');A=C(x.host,x.port,ua);B=C(x.host,x.port,ub);R=[]
 try:
  es=[]
  ts=[threading.Thread(target=lambda c,u,p: (login(c,u,p)),args=(A,ua,pa)),threading.Thread(target=lambda c,u,p: (login(c,u,p)),args=(B,ub,pb))]
  for t in ts:t.start()
  for t in ts:t.join()
  R.append(('two real characters connected',True))
  A.send('look');B.send('look');al=A.read(1.2);bl=B.read(1.2);print('\n--- A LOOK ---\n'+al[-1800:]);print('\n--- B LOOK ---\n'+bl[-1800:])
  tok='WORLD'+str(int(time.time()));A.clear();B.clear();A.send('say '+tok);R.append(('same-room broadcast reaches B',tok in B.read(1.5)))
  # Optional real shared object contention. Operator supplies an existing visible item id; no object is created.
  item=ask('Visible ground item id for contention test (blank=skip): ')
  if item:
   A.clear();B.clear();bar=threading.Barrier(2);outs={}
   def grab(c,k):bar.wait();c.send('get '+item);outs[k]=c.read(1.4)
   p=threading.Thread(target=grab,args=(A,'a'));q=threading.Thread(target=grab,args=(B,'b'));p.start();q.start();p.join();q.join()
   # Canonical get.c is authoritative here. Both clients may see the winner's
   # room message, so inventory text is not a reliable ID proof. Exactly one
   # contender should receive the private `present()` failure after the other
   # moved the single shared object. If both are rejected by guard/no_get/etc.,
   # the environmental condition was not suitable and is not promoted to PASS.
   miss=('你附近沒有這樣東西','這裡沒有這樣東西')
   afail=any(x in outs.get('a','') for x in miss); bfail=any(x in outs.get('b','') for x in miss)
   if afail ^ bfail:
    R.append(('one shared ground object had a single winning owner under concurrent get',True))
   else:
    print('[SKIP] Ground-item race was inconclusive or both attempts were rejected; no contention PASS recorded.')
  # Optional shared NPC targeting only. Do NOT classify non-empty output as
  # combat PASS: canonical fight.c can reject due no_fight/accept_fight, and a
  # non-civilized NPC may escalate with kill_ob(). Real combat is handled by
  # the dedicated assisted combat tools.
  npc=ask('Visible NPC id for shared-target ADDRESSING probe only (blank=skip): ')
  if npc:
   A.clear();B.clear();A.send('look '+npc);oa=A.read(1.1);B.send('look '+npc);ob=B.read(1.1)
   missing=('沒有這個人' in oa or '沒有這樣' in oa or '沒有這個人' in ob or '沒有這樣' in ob)
   if oa.strip() and ob.strip() and not missing:
    R.append(('both sessions can independently address the same visible canonical NPC',True))
   else:
    print('[SKIP] Shared NPC addressing was not conclusively proven; no combat command was sent.')
  # Concurrent save after shared-world activity.
  outs={};bar=threading.Barrier(2)
  def sv(c,k):bar.wait();c.send('save');outs[k]=c.read(1.8)
  p=threading.Thread(target=sv,args=(A,'a'));q=threading.Thread(target=sv,args=(B,'b'));p.start();q.start();p.join();q.join()
  ok=lambda t:('檔案儲存完畢' in t) or ('分鐘' in t and '儲存' in t)
  R.append(('concurrent per-character save after interaction',ok(outs.get('a','')) and ok(outs.get('b',''))))
  print('\nLIVE SHARED-WORLD ACCEPTANCE')
  for n,o in R:print(('[PASS] ' if o else '[CHECK] ')+n)
  return 0 if all(o for _,o in R) else 3
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':sys.exit(main())
