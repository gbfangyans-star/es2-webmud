#!/usr/bin/env node
import fs from 'node:fs';
const p=process.argv[2]; if(!p){console.error('report path required');process.exit(2)}
const x=JSON.parse(fs.readFileSync(p,'utf8'));
const required=['score','hp','skills','inventory','look','movement'];
const missing=required.filter(k=>!x.coverage?.[k]);
const invalid=x.steps?.filter(s=>!s.ok)||[];
const out={ok:missing.length===0&&invalid.length===0,missing,invalidSteps:invalid.map(x=>x.line),steps:x.steps?.length||0};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
