#!/usr/bin/env node
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {spawnSync} from 'node:child_process';
const dir=path.resolve(process.argv[2]||'');
if(!dir){console.error('usage: validate_session_package.mjs package-dir');process.exit(2)}
let manifest;try{manifest=JSON.parse(fs.readFileSync(path.join(dir,'manifest.json'),'utf8'))}catch(e){console.log(JSON.stringify({ok:false,issues:[{kind:'manifest_invalid',error:e.message}]},null,2));process.exit(2)}
const issues=[];
for(const [key,rec] of Object.entries(manifest.files||{})){
 const p=path.resolve(dir,rec.file);
 if(!p.startsWith(dir+path.sep)&&p!==dir){issues.push({kind:'path_rejected',key});continue}
 if(!fs.existsSync(p)){issues.push({kind:'file_missing',key,file:rec.file});continue}
 const data=fs.readFileSync(p),sha=crypto.createHash('sha256').update(data).digest('hex');
 if(data.length!==rec.bytes)issues.push({kind:'size_mismatch',key});
 if(sha!==rec.sha256)issues.push({kind:'sha256_mismatch',key,expected:rec.sha256,actual:sha});
}
const chainTool=new URL('./validate_session_chain.mjs',import.meta.url).pathname;
const c=spawnSync('node',[chainTool,path.join(dir,'session.jsonl'),path.join(dir,'session-chain.json')],{encoding:'utf8'});
if(c.status!==0)issues.push({kind:'chain_invalid'});
let acceptance={};try{acceptance=JSON.parse(fs.readFileSync(path.join(dir,'acceptance.json'),'utf8'))}catch{}
if(manifest.acceptanceComplete!==!!acceptance.complete)issues.push({kind:'acceptance_manifest_mismatch'});
const out={ok:issues.length===0,acceptanceComplete:!!acceptance.complete,issues};
console.log(JSON.stringify(out,null,2));process.exit(out.ok?0:2);
