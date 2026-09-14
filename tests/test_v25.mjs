import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';

const root=new URL('../',import.meta.url).pathname;
const tool=n=>path.join(root,'tools',n);
const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v25-'));

// 1. Build a complete captured-session package.
const session=path.join(dir,'session.jsonl');
const rows=[
 {command:'score',response:'目前是等級 3\n累積業力共 10 點\n'},
 {command:'hp',response:'形體 10/10    精 10/10    氣 10/10    神 10/10\n食物 10/10    飲水 10/10    疲勞 0/10\n'},
 {command:'skills',response:'目前並沒有學會任何技能。\n'},
 {command:'inventory',response:'目前你身上沒有任何東西。\n'},
 {command:'look',response:'你攻擊對手。\n你的眼前一黑，接著什麼也不知道了....\n慢慢地你終於又有了知覺....\n你死了！！\n重新連線完畢。\n'},
 {command:'go north',response:'北方景象。\n'}
];
fs.writeFileSync(session,rows.map(x=>JSON.stringify(x)).join('\n'));
const sessionPkg=path.join(dir,'session-package');
execFileSync('node',[tool('build_session_package.mjs'),'--session',session,'--out',sessionPkg],{stdio:'pipe'});
let v=JSON.parse(execFileSync('node',[tool('validate_session_package.mjs'),sessionPkg],{encoding:'utf8'}));
assert.equal(v.ok,true);assert.equal(v.acceptanceComplete,true);

// Tamper detection.
const pkgSession=path.join(sessionPkg,'session.jsonl');
const original=fs.readFileSync(pkgSession,'utf8');
fs.writeFileSync(pkgSession,original.replace('北方景象','竄改景象'));
let bad=spawnSync('node',[tool('validate_session_package.mjs'),sessionPkg],{encoding:'utf8'});
assert.notEqual(bad.status,0);
fs.writeFileSync(pkgSession,original);

// 2. Build evidence-backed multiplayer plan.
const plan=path.join(dir,'multiplayer.json');
execFileSync('node',[tool('new_multiplayer_test_plan.mjs'),plan],{stdio:'pipe'});
const ids=['bridge-10','bridge-50','login-isolation','same-room','chat','movement-isolation','combat-isolation','disconnect-one','reconnect'];
for(const id of ids){
 const ev=path.join(dir,`${id}.txt`);fs.writeFileSync(ev,`live evidence for ${id}\n`);
 execFileSync('node',[tool('attach_multiplayer_evidence.mjs'),'--plan',plan,'--stage',id,'--evidence',ev],{stdio:'pipe'});
}
v=JSON.parse(execFileSync('node',[tool('validate_multiplayer_plan.mjs'),'--plan',plan],{encoding:'utf8'}));
assert.equal(v.ok,true);

// 3. Build + hash-validate runtime evidence bundle.
const evNames=['source-status.json','runtime-smoke.json','login.txt','movement.txt','combat.txt','reconnect.txt'];
for(const n of evNames)fs.writeFileSync(path.join(dir,n),`evidence ${n}\n`);
const bundle=path.join(dir,'runtime-bundle');
execFileSync('python',[tool('evidence_bundle.py'),bundle,
 '--source-status',path.join(dir,evNames[0]),'--runtime-smoke',path.join(dir,evNames[1]),
 '--login-transcript',path.join(dir,evNames[2]),'--movement-transcript',path.join(dir,evNames[3]),
 '--combat-transcript',path.join(dir,evNames[4]),'--reconnect-transcript',path.join(dir,evNames[5])],{stdio:'pipe'});
v=JSON.parse(execFileSync('python',[tool('validate_runtime_evidence.py'),bundle],{encoding:'utf8'}));
assert.equal(v.ok,true);
const tamper=path.join(bundle,'combat.txt');const combatOriginal=fs.readFileSync(tamper,'utf8');fs.appendFileSync(tamper,'tamper');
bad=spawnSync('python',[tool('validate_runtime_evidence.py'),bundle],{encoding:'utf8'});assert.notEqual(bad.status,0);fs.writeFileSync(tamper,combatOriginal);

// 4. End-to-end final campaign gate.
const release=path.join(dir,'release.json');fs.writeFileSync(release,JSON.stringify({ok:true,version:'2.5.0'}));
const final=path.join(dir,'final.json');
execFileSync('python',[tool('final_campaign_gate.py'),'--release',release,'--runtime-bundle',bundle,'--session-package',sessionPkg,'--multiplayer',plan,'--out',final],{stdio:'pipe'});
const finalReport=JSON.parse(fs.readFileSync(final,'utf8'));assert.equal(finalReport.ok,true);
console.log('v2.5 full validation campaign tests passed');
