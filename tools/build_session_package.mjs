#!/usr/bin/env node
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {execFileSync,spawnSync} from 'node:child_process';
const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.session||!opt.out||!opt.campaign){
 console.error('usage: build_session_package.mjs --session es2-session.jsonl --out session-package-dir --campaign campaign.json');
 process.exit(2)
}
function campaignBinding(file){
 const data=fs.readFileSync(path.resolve(file));
 const x=JSON.parse(data.toString('utf8'));
 if(x.format!=='es2-validation-campaign-v1')throw new Error('invalid campaign format');
 if(!x.campaignId||!x.projectVersion||!x.source?.mudlibTreeSha256)throw new Error('campaign provenance incomplete');
 return {
  campaignId:x.campaignId,
  campaignSha256:crypto.createHash('sha256').update(data).digest('hex'),
  projectVersion:x.projectVersion,
  sourceCommit:x.source.commit||null,
  mudlibTreeSha256:x.source.mudlibTreeSha256
 };
}
const binding=campaignBinding(opt.campaign);
const session=path.resolve(opt.session),out=path.resolve(opt.out);fs.mkdirSync(out,{recursive:true});
const tool=n=>new URL(`./${n}`,import.meta.url).pathname;
const files={
 session:path.join(out,'session.jsonl'),
 replay:path.join(out,'replay.json'),
 evidence:path.join(out,'session-evidence.json'),
 chain:path.join(out,'session-chain.json'),
 movement:path.join(out,'movement-transition.json'),
 acceptance:path.join(out,'acceptance.json')
};
fs.copyFileSync(session,files.session);
execFileSync('node',[tool('replay_session.mjs'),'--in',files.session,'--out',files.replay],{stdio:'pipe'});
execFileSync('node',[tool('build_session_evidence.mjs'),'--session',files.session,'--out',files.evidence],{stdio:'pipe'});
execFileSync('node',[tool('hash_session_chain.mjs'),'--session',files.session,'--out',files.chain],{stdio:'pipe'});
const movement=spawnSync('node',[tool('verify_movement_transition.mjs'),'--session',files.session,'--out',files.movement],{encoding:'utf8'});
execFileSync('node',[tool('build_acceptance_matrix.mjs'),'--replay',files.replay,'--movement',files.movement,'--out',files.acceptance],{stdio:'pipe'});
const chainCheck=spawnSync('node',[tool('validate_session_chain.mjs'),files.session,files.chain],{encoding:'utf8'});
const acceptance=JSON.parse(fs.readFileSync(files.acceptance,'utf8'));
const entries={};
for(const [key,p] of Object.entries(files)){
 const data=fs.readFileSync(p);entries[key]={file:path.basename(p),bytes:data.length,sha256:crypto.createHash('sha256').update(data).digest('hex')};
}
const manifest={
 format:'es2-session-package-v3',
 generatedAt:new Date().toISOString(),
 campaignBinding:binding,
 sourceSession:path.basename(session),
 chainValid:chainCheck.status===0,
 movementEvidencePresent:true,
 movementPass:movement.status===0,
 acceptanceComplete:!!acceptance.complete,
 files:entries,
 note:'Package built only from captured session evidence. No gameplay is executed or synthesized.'
};
fs.writeFileSync(path.join(out,'manifest.json'),JSON.stringify(manifest,null,2));
console.log(JSON.stringify({ok:manifest.chainValid,out,campaignId:binding.campaignId,movementPass:manifest.movementPass,acceptanceComplete:manifest.acceptanceComplete},null,2));
process.exit(manifest.chainValid?0:2);
