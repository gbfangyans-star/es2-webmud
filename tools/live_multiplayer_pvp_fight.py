#!/usr/bin/env python3
"""Low-risk real-Neolith two-player mutual `fight` acceptance.

This intentionally tests player-vs-player `fight`, not `kill`. Canonical fight.c
requires mutual consent for userp targets and establishes fight_ob on both sides.
The tool first proves same-room visibility, asks for explicit operator approval,
performs A->B then B->A consent, observes briefly, and halts both players.
It never sends `kill`, creates objects, teleports, or edits saves.
"""
import argparse,getpass,re,socket,sys,threading,time
IAC=255;DO=253;DONT=254;WILL=251;WONT=252;SB=250;SE=240
SKIP=4

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
  ta=threading.Thread(target=lg,args=(A,ua,pa));tb=threading.Thread(target=lg,args=(B,ub,pb));ta.start();tb.start();ta.join();tb.join()
  if errs:raise RuntimeError('; '.join(errs))
  A.send('look');B.send('look');al=A.read(1.2);bl=B.read(1.2)
  print('\n--- A LOOK ---\n'+al[-1600:]);print('\n--- B LOOK ---\n'+bl[-1600:])
  tok='PVPROOM'+str(int(time.time()));A.clear();B.clear();A.send('say '+tok)
  if tok not in B.read(1.5):
   print('[STOP] Same-room presence not proven. No fight command sent.');return 3
  print('\nSAFETY: this sends only canonical player `fight`; NEVER `kill`.')
  print('Canonical user-vs-user fight requires mutual consent.')
  if input('Type exactly TYPE PVP FIGHT to continue: ').strip()!='TYPE PVP FIGHT':
   print('[SKIP] Operator cancelled.');return SKIP
  A.clear();B.clear();A.send('fight '+ub);oa=A.read(1.1);ob=B.read(.8)
  combined1=oa+ob
  if '這裡禁止戰鬥' in combined1:
   print('[CONDITION NOT MET] Current canonical room forbids combat. No combat began.');return SKIP
  if '這人現在不在線上' in combined1 or '你想攻擊誰' in combined1:
   print('[FAIL] Targeting failed.');return 3
  # B consents to A's challenge.
  A.clear();B.clear();B.send('fight '+ua);ob2=B.read(1.1);oa2=A.read(.8)
  time.sleep(.35);A.send('halt');B.send('halt');ha=A.read(1.2);hb=B.read(1.2)
  print('\n--- A ---\n'+(oa+oa2+ha)[-1600:]);print('\n--- B ---\n'+(ob+ob2+hb)[-1600:])
  if '這裡禁止戰鬥' in (ob2+oa2):
   print('[CONDITION NOT MET] Current canonical room forbids combat.');return SKIP
  started=not('你現在並沒有在戰鬥' in ha and '你現在並沒有在戰鬥' in hb)
  halted=(('Ok.' in ha) or ('罷手不鬥' in ha)) and (('Ok.' in hb) or ('罷手不鬥' in hb))
  consent=('必須等對方同意' in combined1) or ('請你也對' in combined1)
  if consent and started and halted:
   print('\n[PASS] Mutual player fight consent, shared combat state, and halt cleanup were proven live.')
   return 0
  print('\n[CHECK] Live PvP fight did not prove every expected state. No kill command was sent.')
  return 3
 except Exception as e:print('[FAIL]',e);return 2
 finally:A.close();B.close()
if __name__=='__main__':raise SystemExit(main())
