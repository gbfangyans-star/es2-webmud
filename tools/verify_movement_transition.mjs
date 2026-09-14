#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';

const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.session){console.error('usage: verify_movement_transition.mjs --session session.jsonl [--out movement.json]');process.exit(2)}
const rows=fs.readFileSync(opt.session,'utf8').split(/\r?\n/).filter(Boolean).map((x,i)=>({line:i+1,...JSON.parse(x)}));
const clean=s=>String(s||'').replace(/\x1b\[[0-9;]*m/g,'').replace(/\r/g,'').trim();
const failNeedles=[
 '你要往哪個方向走','要移動請你先用 halt 終止你正在做的事','你的負荷過重',
 '你哪裡也去不了','你已經無路可逃了','這個方向沒有出路','這一個方向的出口有問題'
];
const transitions=[];
for(let i=0;i<rows.length;i++){
  const go=rows[i],cmd=String(go.command||'').trim();
  if(!/^go(?:\s+|$)/.test(cmd))continue;
  const before=[...rows.slice(0,i)].reverse().find(r=>String(r.command||'').trim()==='look');
  const after=rows.slice(i+1).find(r=>String(r.command||'').trim()==='look');
  const goText=clean(go.response);
  const blocked=failNeedles.some(x=>goText.includes(x))||/你被.+擋住了/.test(goText);
  if(!before||!after){
    transitions.push({goLine:go.line,command:cmd,pass:false,reason:'look_before_or_after_missing',blocked});
    continue;
  }
  const b=clean(before.response),a=clean(after.response);
  const bHash=crypto.createHash('sha256').update(b).digest('hex');
  const aHash=crypto.createHash('sha256').update(a).digest('hex');
  const different=!!b&&!!a&&bHash!==aHash;
  transitions.push({
    goLine:go.line,command:cmd,beforeLookLine:before.line,afterLookLine:after.line,
    blocked,beforeBytes:Buffer.byteLength(b),afterBytes:Buffer.byteLength(a),
    beforeSha256:bHash,afterSha256:aHash,different,
    pass:!blocked&&different,
    reason:blocked?'canonical_go_failure_observed':(!different?'look_output_unchanged':null)
  });
}
const out={
  format:'es2-movement-transition-evidence-v1',
  ok:transitions.some(x=>x.pass),
  transitions,
  rule:'PASS requires captured look before + go without canonical failure + captured look after with different normalized raw output. This is observational runtime evidence; it does not make the browser authoritative.'
};
if(opt.out)fs.writeFileSync(opt.out,JSON.stringify(out,null,2));
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
