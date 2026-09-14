#!/usr/bin/env node
import net from 'node:net';
import {spawn} from 'node:child_process';
import WebSocket from '../server/node_modules/ws/index.js';
import path from 'node:path';
import {fileURLToPath} from 'node:url';

const here=path.dirname(fileURLToPath(import.meta.url));
const root=path.resolve(here,'..');
async function freePort(){const x=net.createServer();await new Promise((r,j)=>{x.once('error',j);x.listen(0,'127.0.0.1',r)});const p=x.address().port;await new Promise(r=>x.close(r));return p;}
const mudPort=await freePort();
const webPort=await freePort();
let seq=0;
const mud=net.createServer(sock=>{
  const id=++seq;
  sock.setNoDelay(true);
  sock.write(`WELCOME:${id}\r\n`);
  sock.on('data',d=>sock.write(`ECHO:${id}:${String(d)}`));
});
await new Promise((resolve,reject)=>{mud.once('error',reject);mud.listen(mudPort,'127.0.0.1',resolve)});

const child=spawn(process.execPath,['server/index.js'],{
  cwd:root,
  env:{...process.env,HOST:'127.0.0.1',PORT:String(webPort),MUD_HOST:'127.0.0.1',MUD_PORT:String(mudPort),MAX_SESSIONS:'16'},
  stdio:['ignore','pipe','pipe']
});
let log='';child.stdout.on('data',d=>log+=d);child.stderr.on('data',d=>log+=d);
const wait=ms=>new Promise(r=>setTimeout(r,ms));
for(let i=0;i<80&&!log.includes('ES2 WebMUD');i++)await wait(50);
if(!log.includes('ES2 WebMUD')){child.kill();mud.close();throw new Error('bridge did not start: '+log)}

const N=8;
const rows=[];
await Promise.all(Array.from({length:N},(_,i)=>new Promise((resolve,reject)=>{
  const ws=new WebSocket(`ws://127.0.0.1:${webPort}/mud`);
  let text='';
  const timer=setTimeout(()=>{try{ws.close()}catch{};reject(new Error(`client ${i+1} timeout: ${text}`))},5000);
  ws.on('message',d=>{
    text+=String(d);
    const welcome=text.match(/WELCOME:(\d+)/);
    if(welcome && text.includes(`ECHO:${welcome[1]}:client-${i+1}`)){
      clearTimeout(timer);rows.push({client:i+1,tcp:Number(welcome[1]),text});ws.close();resolve();
    }
  });
  ws.on('open',()=>ws.send(`client-${i+1}\r\n`));
  ws.on('error',e=>{clearTimeout(timer);reject(e)});
})));
const ids=rows.map(r=>r.tcp);
const unique=new Set(ids).size===N;
let crossed=false;
for(const r of rows){
  for(let j=1;j<=N;j++)if(j!==r.client && r.text.includes(`client-${j}`))crossed=true;
}
const result={ok:unique&&!crossed,clients:N,uniqueTcpSessions:new Set(ids).size,crossTalk:crossed,rows:rows.sort((a,b)=>a.client-b.client).map(({client,tcp})=>({client,tcp}))};
console.log(JSON.stringify(result,null,2));
child.kill();await new Promise(r=>mud.close(r));
process.exit(result.ok?0:2);
