#!/usr/bin/env node
import { readFileSync } from 'node:fs';
import net from 'node:net';
import {spawn} from 'node:child_process';
import WebSocket from '../server/node_modules/ws/index.js';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
const here=path.dirname(fileURLToPath(import.meta.url)), root=path.resolve(here,'..');
const wait=ms=>new Promise(r=>setTimeout(r,ms));
async function freePort(){const x=net.createServer();await new Promise((r,j)=>{x.once('error',j);x.listen(0,'127.0.0.1',r)});const p=x.address().port;await new Promise(r=>x.close(r));return p;}
const mudPort=await freePort(), webPort=await freePort();
let tcpSeq=0;
const mud=net.createServer(sock=>{const id=++tcpSeq;sock.setNoDelay(true);sock.write(`WELCOME:${id}\r\n`);sock.on('data',d=>sock.write(`ECHO:${id}:${String(d)}`));});
await new Promise((res,rej)=>{mud.once('error',rej);mud.listen(mudPort,'127.0.0.1',res)});
const child=spawn(process.execPath,['server/index.js'],{cwd:root,env:{...process.env,HOST:'127.0.0.1',PORT:String(webPort),MUD_HOST:'127.0.0.1',MUD_PORT:String(mudPort),MAX_SESSIONS:'80',HEARTBEAT_MS:'2000'},stdio:['ignore','pipe','pipe']});
let log='';child.stdout.on('data',d=>log+=d);child.stderr.on('data',d=>log+=d);
for(let i=0;i<100&&!log.includes('ES2 WebMUD');i++)await wait(50);if(!log.includes('ES2 WebMUD'))throw new Error('bridge did not start '+log);
async function client(label){return new Promise((resolve,reject)=>{const ws=new WebSocket(`ws://127.0.0.1:${webPort}/mud`);let text='',id=null;const timer=setTimeout(()=>{try{ws.terminate()}catch{};reject(new Error('timeout '+label))},5000);ws.on('message',d=>{text+=String(d);const m=text.match(/WELCOME:(\d+)/);if(m)id=Number(m[1]);if(id&&text.includes(`ECHO:${id}:${label}`)){clearTimeout(timer);ws.close();resolve({id,text})}});ws.on('open',()=>ws.send(label+'\r\n'));ws.on('error',e=>{clearTimeout(timer);reject(e)})})}
const waves=20, perWave=25;let failures=[],crossTalk=false,total=0;
for(let w=1;w<=waves;w++){
 const labels=Array.from({length:perWave},(_,i)=>`<ENDURANCE-${w}-${i+1}>`);
 const rows=await Promise.all(labels.map(async l=>{try{return {label:l,...await client(l)}}catch(e){failures.push({label:l,error:String(e)});return null}}));
 total+=labels.length;
 for(const r of rows.filter(Boolean))for(const l of labels)if(l!==r.label&&r.text.includes(l))crossTalk=true;
 await wait(40);
}
await wait(500);
const health=await fetch(`http://127.0.0.1:${webPort}/api/multiplayer-health`).then(r=>r.json());
const clean=health.sessions.active===0&&health.sessions.connected===0;
const release=readFileSync(new URL('../VERSION',import.meta.url),'utf8').trim();
const result={version:release,ok:!failures.length&&!crossTalk&&clean,totalSessions:total,waves,clientsPerWave:perWave,failures,crossTalk,cleanupAfterEndurance:clean,health};
console.log(JSON.stringify(result,null,2));child.kill('SIGTERM');await wait(100);await new Promise(r=>mud.close(r));process.exit(result.ok?0:2);
