#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
const [session,chainFile]=process.argv.slice(2);
if(!session||!chainFile){
  console.error('usage: validate_session_chain.mjs session.jsonl chain.json');
  process.exit(2);
}
const rows=fs.readFileSync(session,'utf8').split(/\r?\n/).filter(Boolean);
const chain=JSON.parse(fs.readFileSync(chainFile,'utf8'));
let prev='0'.repeat(64),ok=rows.length===chain.records;
for(let i=0;i<rows.length;i++){
  const obj=JSON.parse(rows[i]);
  const hash=crypto.createHash('sha256').update(prev+'\n'+JSON.stringify(obj)).digest('hex');
  const c=chain.chain?.[i];
  if(!c||c.prevHash!==prev||c.recordHash!==hash){ok=false;break}
  prev=hash;
}
if(chain.lastHash!==(rows.length?prev:null))ok=false;
console.log(JSON.stringify({ok,records:rows.length,lastHash:rows.length?prev:null},null,2));
process.exit(ok?0:2);
