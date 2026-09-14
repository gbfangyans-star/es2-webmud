#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
import path from 'node:path';
const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.plan||!opt.stage||!opt.evidence){console.error('usage: attach_multiplayer_evidence.mjs --plan plan.json --stage same-room --evidence file.txt');process.exit(2)}
const planPath=path.resolve(opt.plan),base=path.dirname(planPath),source=path.resolve(opt.evidence);
const x=JSON.parse(fs.readFileSync(planPath,'utf8'));
const s=(x.stages||[]).find(z=>z.id===opt.stage);
if(!s){console.error('unknown stage');process.exit(2)}
const data=fs.readFileSync(source);
if(!data.length){console.error('evidence file is empty');process.exit(2)}
const evidenceDir=path.join(base,'multiplayer-evidence');fs.mkdirSync(evidenceDir,{recursive:true});
const safeBase=path.basename(source).replace(/[^A-Za-z0-9._-]+/g,'_');
const dst=path.join(evidenceDir,`${s.id}__${safeBase}`);
fs.writeFileSync(dst,data);
s.status='pass';
s.evidenceFile=path.relative(base,dst).replaceAll('\\','/');
s.sha256=crypto.createHash('sha256').update(data).digest('hex');
s.bytes=data.length;
s.recordedAt=new Date().toISOString();
fs.writeFileSync(planPath,JSON.stringify(x,null,2));
console.log(JSON.stringify({ok:true,stage:s.id,evidenceFile:s.evidenceFile,sha256:s.sha256,bytes:s.bytes},null,2));
