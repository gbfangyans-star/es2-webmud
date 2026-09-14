#!/usr/bin/env python3
"""Operator-assisted shared-NPC combat *probe* against real Neolith.

Safety model:
- never sends `kill`, never spawns, never teleports;
- proves same-room addressing and canonical room/NPC response;
- does NOT call an arbitrary NPC fight "non-lethal": canonical fight.c allows a
  non-civilized NPC to answer with kill_ob(), so an accepted NPC fight can be risky;
- if the room rejects combat or the NPC refuses, returns CONDITION_NOT_MET (4), not PASS;
- if combat actually begins, immediately issues canonical `halt` to both test players.

Use the separate PvP mutual-fight acceptance for the preferred low-risk live combat gate.
Passwords remain memory-only.
"""
import argparse,getpass,re,socket,sys,threading,time
IAC=255;DO=253;DONT=254;WILL=251;WONT=252;SB=250;SE=240
CONDITION_NOT_MET=4

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

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000);ap.add_argument('--user-a');ap.add_argument('--user-b');a=ap.parse_args()
 ua=(a.user_a or input('Existing user A: ')).strip().lower();ub=(a.user_b or input('Existing user B: ')).strip().lower()
 if not ua or not ub or ua==ub:print('Need two different existing ids.');return 2
 pa=getpass.getpass('Password for '+ua+': ');pb=getpass.getpass('Password for '+ub+': ')
 A=C(a.host,a.port,ua);B=C(a.host,a.port,ub)
 try:
  errs=[]
  def lg(c,u,p):
   try:login(c,u,p)
   except Exception as e:errs.append(str(e))
  x=threading.Thread(target=lg,args=(A,ua,pa));y=threading.Thread(target=lg,args=(B,ub,pb));x.start();y.start();x.join();y.join()
  if errs:raise RuntimeError('; '.join(errs))
  A.send('look');B.send('look');al=A.read(1.2);bl=B.read(1.2)
  print('\n--- A LOOK ---\n'+al[-1800:]);print('\n--- B LOOK ---\n'+bl[-1800:])
  tok='COMBATROOM'+str(int(time.time()));A.clear();B.clear();A.send('say '+tok)
  if tok not in B.read(1.5):
   print('[STOP] Characters are not proven to share a room. No combat command was sent.');return 3
  npc=input('Visible canonical NPC id for RISKY fight probe (blank=skip): ').strip()
  if not npc:
   print('[SKIP] No NPC selected. No combat command was sent.');return CONDITION_NOT_MET
  print('\nWARNING: canonical fight.c can make a non-civilized NPC answer with kill_ob().')
  print('Preferred safe combat verification is CHECK_MULTIPLAYER_PVP_FIGHT_LIVE.bat.')
  confirm=input('Type exactly TYPE RISKY FIGHT to continue: ').strip()
  if confirm!='TYPE RISKY FIGHT':
   print('[CANCELLED] No combat command was sent.');return CONDITION_NOT_MET
  A.clear();B.clear();A.send('fight '+npc);oa=A.read(.9);B.send('fight '+npc);ob=B.read(.9)
  time.sleep(.25);A.send('halt');B.send('halt');ca=A.read(1.2);cb=B.read(1.2)
  combined=(oa+ob+ca+cb)
  print('\n--- A FIGHT/HALT ---\n'+(oa+ca)[-1400:]);print('\n--- B FIGHT/HALT ---\n'+(ob+cb)[-1400:])
  rejection_terms=('這裡禁止戰鬥','並不想跟你較量','你想攻擊誰','不行。','看不見你','是你的師父','你不能攻擊自己','這人現在不在線上')
  if any(t in combined for t in rejection_terms) or ('你現在並沒有在戰鬥' in ca and '你現在並沒有在戰鬥' in cb):
   print('\n[CONDITION NOT MET] Canonical room/NPC rejected or never entered combat.')
   print('This is not a multiplayer failure and is NOT recorded as combat PASS.')
   return CONDITION_NOT_MET
  halted=('Ok.' in ca or '罷手不鬥' in ca) and ('Ok.' in cb or '罷手不鬥' in cb)
  if not halted:
   print('\n[CHECK] Combat may have started, but clean halt was not proven for both sessions.')
   return 3
  print('\n[PASS] Both sessions reached canonical combat and both cleanly halted.')
  return 0
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':sys.exit(main())
