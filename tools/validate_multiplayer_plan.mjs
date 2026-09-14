#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
import path from 'node:path';
const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.plan){console.error('usage: validate_multiplayer_plan.mjs --plan plan.json');process.exit(2)}
const planPath=path.resolve(opt.plan),base=path.dirname(planPath);
const x=JSON.parse(fs.readFileSync(planPath,'utf8'));
const required=['bridge-10','bridge-50','login-isolation','same-room','chat','movement-isolation','combat-isolation','disconnect-one','reconnect'];
const byId=new Map((x.stages||[]).map(s=>[s.id,s]));
const issues=[];
for(const id of required){
  const s=byId.get(id);
  if(!s){issues.push({kind:'stage_missing',stage:id});continue}
  if(s.status!=='pass'){issues.push({kind:'stage_not_pass',stage:id,status:s.status||null});continue}
  if(!s.evidenceFile){issues.push({kind:'evidence_missing',stage:id});continue}
  const p=path.resolve(base,s.evidenceFile);
  if(!p.startsWith(base+path.sep)&&p!==base){issues.push({kind:'evidence_path_rejected',stage:id});continue}
  if(!fs.existsSync(p)){issues.push({kind:'evidence_file_missing',stage:id,file:s.evidenceFile});continue}
  const data=fs.readFileSync(p);
  if(!data.length){issues.push({kind:'evidence_empty',stage:id,file:s.evidenceFile});continue}
  const sha=crypto.createHash('sha256').update(data).digest('hex');
  if(s.sha256&&s.sha256!==sha)issues.push({kind:'evidence_sha256_mismatch',stage:id,expected:s.sha256,actual:sha});
}
const out={ok:issues.length===0,format:x.format,requiredStages:required.length,issues};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
