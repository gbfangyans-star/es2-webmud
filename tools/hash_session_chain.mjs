#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.session||!opt.out){
  console.error('usage: hash_session_chain.mjs --session es2-session.jsonl --out chain.json');
  process.exit(2);
}
const raw=fs.readFileSync(opt.session,'utf8').split(/\r?\n/).filter(Boolean);
let prev='0'.repeat(64);
const records=[];
for(let i=0;i<raw.length;i++){
  const obj=JSON.parse(raw[i]);
  const canonical=JSON.stringify(obj);
  const hash=crypto.createHash('sha256').update(prev+'\n'+canonical).digest('hex');
  records.push({index:i,prevHash:prev,recordHash:hash});
  prev=hash;
}
const out={
  format:'es2-session-chain-v1',
  records:records.length,
  firstHash:records[0]?.recordHash||null,
  lastHash:records.at(-1)?.recordHash||null,
  chain:records
};
fs.writeFileSync(opt.out,JSON.stringify(out,null,2));
console.log(JSON.stringify({ok:true,records:records.length,lastHash:out.lastHash},null,2));
