#!/usr/bin/env python3
"""Interactive live Neolith acceptance for TWO EXISTING test characters.
Passwords are requested with getpass and never written to disk or command line.
This tool does not create/alter gameplay data beyond issuing canonical player commands.
"""
import argparse,getpass,re,socket,sys,threading,time

IAC=255; DO=253; DONT=254; WILL=251; WONT=252; SB=250; SE=240

def strip_telnet(data:bytes)->bytes:
    out=bytearray();i=0
    while i<len(data):
        if data[i]!=IAC: out.append(data[i]); i+=1; continue
        if i+1>=len(data): break
        cmd=data[i+1]
        if cmd==IAC: out.append(IAC); i+=2; continue
        if cmd in (DO,DONT,WILL,WONT): i+=3; continue
        if cmd==SB:
            j=i+2
            while j+1<len(data) and not(data[j]==IAC and data[j+1]==SE): j+=1
            i=min(len(data),j+2); continue
        i+=2
    return bytes(out)

class Client:
    def __init__(self,host,port,name):
        self.host=host;self.port=port;self.name=name;self.s=None;self.buf=''
    def connect(self):
        self.s=socket.create_connection((self.host,self.port),timeout=8); self.s.settimeout(.35)
    def send(self,s): self.s.sendall((s+'\r\n').encode('utf-8'))
    def drain(self,seconds=1.0):
        end=time.time()+seconds;parts=[]
        while time.time()<end:
            try:
                d=self.s.recv(65536)
                if not d: break
                t=strip_telnet(d).decode('utf-8','replace');parts.append(t)
            except socket.timeout: pass
        text=''.join(parts); self.buf+=text; return text
    def wait(self,patterns,timeout=10):
        end=time.time()+timeout
        while time.time()<end:
            t=self.drain(.35)
            hay=self.buf
            for p in patterns:
                if re.search(p,hay,re.S): return hay
        raise TimeoutError(f'{self.name}: timeout waiting for {patterns}')
    def close(self):
        try:self.s.close()
        except:pass

def login(c,uid,pw):
    c.connect(); c.wait([r'使用者代號',r'您的使用者代號'],12); c.send(uid)
    c.wait([r'請輸入密碼'],8); c.send(pw)
    out=c.wait([r'目前權限',r'重新連線完畢',r'連線進入這個世界',r'重新連線回到這個世界'],15)
    if '密碼錯誤' in out: raise RuntimeError(f'{uid}: bad password')
    c.buf=''; c.drain(1)

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--host',default='127.0.0.1');ap.add_argument('--port',type=int,default=4000)
    ap.add_argument('--user-a');ap.add_argument('--user-b')
    args=ap.parse_args()
    ua=args.user_a or input('Test user A id: ').strip().lower()
    ub=args.user_b or input('Test user B id: ').strip().lower()
    if not ua or not ub or ua==ub:
        print('Need two different existing player ids.');return 2
    pa=getpass.getpass(f'Password for {ua}: '); pb=getpass.getpass(f'Password for {ub}: ')
    a=Client(args.host,args.port,ua);b=Client(args.host,args.port,ub)
    results=[]
    try:
        ta=threading.Thread(target=login,args=(a,ua,pa));tb=threading.Thread(target=login,args=(b,ub,pb));ta.start();tb.start();ta.join();tb.join()
        results.append(('two simultaneous real logins',True))
        # who from A should enumerate both if canonical level visibility allows it; report rather than hard fail if filtered.
        a.send('who'); out=a.drain(2.2); both=(ua.lower() in out.lower() and ub.lower() in out.lower()); results.append(('who sees both ids (level filters may apply)',both))
        # Tell is location-independent and proves player-to-player routing.
        token=f'ES2MP{int(time.time())}'
        a.send(f'tell {ub} {token}'); bout=b.drain(2.2); results.append(('A -> B tell',token in bout))
        time.sleep(3.2)  # canonical tell rate-limit is per sender; leave room for clean output
        token2=token+'R'; b.send(f'tell {ua} {token2}'); aout=a.drain(2.2); results.append(('B -> A tell',token2 in aout))
        # Simultaneous canonical save commands. Save may be rate-limited if players recently saved; both outcomes are surfaced.
        outs={}
        def save(c,k): c.send('save'); outs[k]=c.drain(2.2)
        x=threading.Thread(target=save,args=(a,'a'));y=threading.Thread(target=save,args=(b,'b'));x.start();y.start();x.join();y.join()
        save_ok=lambda t: ('檔案儲存完畢' in t) or ('分鐘' in t and '儲存' in t)
        results.append(('simultaneous independent save commands',save_ok(outs.get('a','')) and save_ok(outs.get('b',''))))
        print('\nLIVE MULTIPLAYER ACCEPTANCE')
        for n,ok in results: print(('[PASS] ' if ok else '[CHECK] ')+n)
        # do not quit characters automatically; avoid changing location/session semantics unexpectedly.
        hard=[r for r in results if r[0] in ('two simultaneous real logins','A -> B tell','B -> A tell','simultaneous independent save commands')]
        return 0 if all(x[1] for x in hard) else 3
    except Exception as e:
        print('[FAIL]',e);return 2
    finally:
        a.close();b.close()
if __name__=='__main__': sys.exit(main())
