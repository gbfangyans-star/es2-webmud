#!/usr/bin/env node
import fs from 'node:fs';
const p=process.argv[2];
if(!p){console.error('acceptance matrix path required');process.exit(2)}
const x=JSON.parse(fs.readFileSync(p,'utf8'));
const failed=Object.entries(x.checks||{}).filter(([,v])=>!v.pass).map(([k])=>k);
const out={ok:failed.length===0,failed,complete:!!x.complete};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
