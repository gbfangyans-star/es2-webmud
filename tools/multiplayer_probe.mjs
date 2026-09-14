#!/usr/bin/env node
import WebSocket from '../server/node_modules/ws/index.js';

const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
const url=opt.url||'ws://127.0.0.1:8080/mud';
const clients=Math.max(1,Math.min(200,Number(opt.clients||10)));
const timeout=Math.max(500,Number(opt.timeout||3000));

const rows=[];
await Promise.all(Array.from({length:clients},(_,i)=>new Promise(resolve=>{
  const row={id:i+1,opened:false,connectedBanner:false,closed:false,error:null,bytes:0};
  rows.push(row);
  let done=false;
  const finish=()=>{if(done)return;done=true;try{ws.close()}catch{};resolve()};
  let ws;
  try{
    ws=new WebSocket(url);
    ws.on('open',()=>{row.opened=true});
    ws.on('message',d=>{
      const s=String(d);row.bytes+=Buffer.byteLength(s);
      if(s.includes('[ES2 connected]'))row.connectedBanner=true;
    });
    ws.on('error',e=>{row.error=e.message;finish()});
    ws.on('close',()=>{row.closed=true;finish()});
    setTimeout(finish,timeout);
  }catch(e){row.error=e.message;finish()}
})));
const opened=rows.filter(x=>x.opened).length;
const banners=rows.filter(x=>x.connectedBanner).length;
const errors=rows.filter(x=>x.error).length;
const out={
  ok:opened===clients && banners===clients && errors===0,
  url,clients,opened,connectedBanners:banners,errors,
  isolationClaim:'Each browser WebSocket is expected to map to a distinct TCP connection in server/index.js; this probe verifies concurrent bridge sessions only, not logged-in player interaction.',
  rows
};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
