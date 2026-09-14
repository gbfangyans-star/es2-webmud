#!/usr/bin/env node
import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.out||!opt.campaign){
 console.error('usage: new_multiplayer_test_plan.mjs --out plan.json --campaign campaign.json');
 process.exit(2)
}
const campaignPath=path.resolve(opt.campaign),data=fs.readFileSync(campaignPath),c=JSON.parse(data.toString('utf8'));
if(c.format!=='es2-validation-campaign-v1'||!c.campaignId||!c.source?.mudlibTreeSha256){
 console.error('invalid campaign manifest');process.exit(2)
}
const binding={
 campaignId:c.campaignId,
 campaignSha256:crypto.createHash('sha256').update(data).digest('hex'),
 projectVersion:c.projectVersion,
 sourceCommit:c.source.commit||null,
 mudlibTreeSha256:c.source.mudlibTreeSha256
};
const plan={
  format:'es2-multiplayer-test-plan-v2',
  campaignBinding:binding,
  requiredAccounts:2,
  stages:[
    {id:'bridge-10',status:'pending',proof:'10 concurrent WebSocket sessions receive ES2 connected',evidenceFile:null,sha256:null},
    {id:'bridge-50',status:'pending',proof:'50 concurrent WebSocket sessions receive ES2 connected',evidenceFile:null,sha256:null},
    {id:'login-isolation',status:'pending',proof:'two distinct test accounts retain independent identity/state',evidenceFile:null,sha256:null},
    {id:'same-room',status:'pending',proof:'A and B can observe each other in same canonical room',evidenceFile:null,sha256:null},
    {id:'chat',status:'pending',proof:'A message is observed by B through canonical game output',evidenceFile:null,sha256:null},
    {id:'movement-isolation',status:'pending',proof:'A moves while B remains independently located',evidenceFile:null,sha256:null},
    {id:'combat-isolation',status:'pending',proof:'A/B combat state does not leak across sessions',evidenceFile:null,sha256:null},
    {id:'disconnect-one',status:'pending',proof:'disconnecting A leaves B session operational',evidenceFile:null,sha256:null},
    {id:'reconnect',status:'pending',proof:'A reconnects and canonical reconnect marker is captured',evidenceFile:null,sha256:null}
  ],
  rule:'Do not mark a stage pass without captured live canonical output/evidence from this campaign.'
};
fs.writeFileSync(path.resolve(opt.out),JSON.stringify(plan,null,2));
console.log(JSON.stringify({ok:true,out:path.resolve(opt.out),campaignId:binding.campaignId},null,2));
