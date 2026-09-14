#!/usr/bin/env node
import net from 'node:net';
const host=process.argv[2]||'127.0.0.1';
const port=Number(process.argv[3]||4000);
const count=Math.max(1,Math.min(100,Number(process.argv[4]||20)));
const timeoutMs=5000;
const openOne=i=>new Promise(resolve=>{
  const s=net.createConnection({host,port});let got=false,bytes=0,done=false;
  const finish=(ok,error='')=>{if(done)return;done=true;try{s.destroy()}catch{};resolve({client:i,ok,bytes,error})};
  const timer=setTimeout(()=>finish(false,'timeout'),timeoutMs);
  s.on('connect',()=>{});
  s.on('data',d=>{bytes+=d.length;if(bytes>0&&!got){got=true;clearTimeout(timer);setTimeout(()=>finish(true),100)}});
  s.on('error',e=>{clearTimeout(timer);finish(false,e.message)});
  s.on('close',()=>{if(!done){clearTimeout(timer);finish(got,got?'':'closed before banner')}});
});
const rows=await Promise.all(Array.from({length:count},(_,i)=>openOne(i+1)));
const passed=rows.filter(r=>r.ok).length;
const out={ok:passed===count,host,port,requested:count,acceptedWithBanner:passed,failed:rows.filter(r=>!r.ok)};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
