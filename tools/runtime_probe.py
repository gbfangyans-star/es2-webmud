#!/usr/bin/env python3
import argparse, socket, json, time, select

ap=argparse.ArgumentParser(description="Read-only ES2 TCP smoke probe.")
ap.add_argument("--host",default="127.0.0.1")
ap.add_argument("--port",type=int,default=4000)
ap.add_argument("--timeout",type=float,default=2.0)
ap.add_argument("--max-bytes",type=int,default=32768)
a=ap.parse_args()

result={"ok":False,"host":a.host,"port":a.port,"connected":False,"bytes":0,"sample":"","error":None}
try:
    s=socket.create_connection((a.host,a.port),timeout=a.timeout)
    result["connected"]=True
    s.setblocking(False)
    deadline=time.time()+a.timeout
    chunks=[]
    total=0
    while time.time()<deadline and total<a.max_bytes:
        r,_,_=select.select([s],[],[],0.15)
        if not r:
            continue
        b=s.recv(min(4096,a.max_bytes-total))
        if not b:
            break
        chunks.append(b);total+=len(b)
    s.close()
    raw=b"".join(chunks)
    # Strip a minimal set of telnet negotiation bytes conservatively for display.
    clean=bytearray();i=0
    while i<len(raw):
        if raw[i]==255 and i+1<len(raw):
            cmd=raw[i+1]
            if cmd in (251,252,253,254) and i+2<len(raw):
                i+=3;continue
            if cmd==255:
                clean.append(255);i+=2;continue
            i+=2;continue
        clean.append(raw[i]);i+=1
    text=bytes(clean).decode("utf-8","replace")
    result["bytes"]=len(raw)
    result["sample"]=text[:4000]
    result["ok"]=result["connected"]
except Exception as e:
    result["error"]=str(e)

print(json.dumps(result,ensure_ascii=False,indent=2))
raise SystemExit(0 if result["ok"] else 2)
