#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
import {execFileSync} from 'node:child_process';
import path from 'node:path';

const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.session||!opt.out){console.error('usage: build_session_evidence.mjs --session es2-session.jsonl --out evidence.json');process.exit(2)}
const tmp=opt.out+'.replay.tmp.json';
execFileSync('node',[new URL('./replay_session.mjs',import.meta.url).pathname,'--in',opt.session,'--out',tmp],{stdio:'pipe'});
const replay=JSON.parse(fs.readFileSync(tmp,'utf8'));
fs.unlinkSync(tmp);
const raw=fs.readFileSync(opt.session);
const out={
  format:'es2-session-evidence-v1',
  sourceFile:path.basename(opt.session),
  sourceSha256:crypto.createHash('sha256').update(raw).digest('hex'),
  records:replay.steps.length,
  coverage:replay.coverage,
  navigationFailures:(replay.observations.navigation||[]),
  observedEvents:(replay.observations.events||[]),
  generatedAt:new Date().toISOString(),
  note:'Built from captured browser command/response JSONL; no gameplay execution or simulation performed.'
};
fs.writeFileSync(opt.out,JSON.stringify(out,null,2));
console.log(JSON.stringify({ok:true,out:opt.out,coverage:out.coverage},null,2));
