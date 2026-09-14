import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v26-'));
const good=path.join(dir,'good.jsonl'),bad=path.join(dir,'bad.jsonl');
const rows=[
 {command:'look',response:'廣場中央\\n人聲鼎沸。'},
 {command:'go east',response:''},
 {command:'look',response:'廣場東側\\n東方道路延伸。'}
];
fs.writeFileSync(good,rows.map(JSON.stringify).join('\n'));
fs.writeFileSync(bad,[rows[0],{command:'go east',response:'這個方向沒有出路。'},rows[0]].map(JSON.stringify).join('\n'));
const tool=new URL('../tools/verify_movement_transition.mjs',import.meta.url).pathname;
const gout=JSON.parse(execFileSync('node',[tool,'--session',good],{encoding:'utf8'}));
assert.equal(gout.ok,true);
const bp=spawnSync('node',[tool,'--session',bad],{encoding:'utf8'});
assert.notEqual(bp.status,0);
console.log('v2.6 movement transition tests passed');
