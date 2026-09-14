#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
import {PlayerStateObserver} from '../web/player_state.js';

const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.in||!opt.out){console.error('usage: replay_session.mjs --in session.jsonl --out report.json');process.exit(2)}
const source=fs.readFileSync(opt.in,'utf8');
const observer=new PlayerStateObserver();
const steps=[];
let lineNo=0;
for(const raw of source.split(/\r?\n/)){
  lineNo++; if(!raw.trim())continue;
  let rec;
  try{rec=JSON.parse(raw)}catch{steps.push({line:lineNo,ok:false,error:'invalid_json'});continue}
  const command=String(rec.command||'').trim();
  const response=String(rec.response||'');
  const op=command.split(/\s+/)[0]||'';
  observer.begin(op,command);
  observer.consume(response);
  const nav=observer.state.navigation.at(-1);
  steps.push({
    line:lineNo,ok:true,command,operation:op,responseBytes:Buffer.byteLength(response),
    navigation:nav?.command===command?nav:null
  });
}
const report={
  format:'es2-session-replay-v1',
  sourceSha256:crypto.createHash('sha256').update(source).digest('hex'),
  steps,
  observations:observer.state,
  coverage:{
    score:steps.some(x=>x.operation==='score'),
    hp:steps.some(x=>x.operation==='hp'),
    skills:steps.some(x=>x.operation==='skills'),
    inventory:steps.some(x=>x.operation==='inventory'),
    look:steps.some(x=>x.operation==='look'),
    movement:steps.some(x=>x.operation==='go')
  },
  note:'Replay parses captured canonical command responses only; it does not execute or simulate gameplay.'
};
fs.writeFileSync(opt.out,JSON.stringify(report,null,2));
console.log(JSON.stringify({ok:true,out:opt.out,steps:steps.length,coverage:report.coverage},null,2));
