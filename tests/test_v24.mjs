import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';
import {SessionRecorder} from '../web/session_recorder.js';

class MemStorage{
  constructor(){this.m=new Map()}
  setItem(k,v){this.m.set(k,String(v))}
  getItem(k){return this.m.has(k)?this.m.get(k):null}
  removeItem(k){this.m.delete(k)}
}
const storage=new MemStorage();
const r=new SessionRecorder({storage});
r.markTransportOpen();
r.beginCommand('secret-password',{sensitive:true});
assert.equal(r.toJSONL().includes('secret-password'),false);
assert.equal(JSON.stringify(r.manifest()).includes('secret-password'),false);
assert.equal(JSON.stringify(r.snapshot()).includes('secret-password'),false);
assert.equal(r.manifest().privacy.redactedEvents,1);

r.beginCommand('score');
r.appendResponse('角色狀態\\n');
r.finishResponse();
assert.equal(r.records[0].command,'score');
assert.equal(r.records[0].response,'角色狀態\\n');

const restored=new SessionRecorder({storage});
assert.equal(restored.records.length,1);
assert.equal(restored.records[0].response,'角色狀態\\n');
assert.equal(restored.manifest().transport.opened,true);

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v24-'));
const session=path.join(dir,'session.jsonl');
const chain=path.join(dir,'chain.json');
fs.writeFileSync(session,restored.toJSONL());
execFileSync('node',[new URL('../tools/hash_session_chain.mjs',import.meta.url).pathname,'--session',session,'--out',chain],{stdio:'pipe'});
execFileSync('node',[new URL('../tools/validate_session_chain.mjs',import.meta.url).pathname,session,chain],{stdio:'pipe'});
fs.writeFileSync(session,restored.toJSONL().replace('角色狀態','竄改'));
const bad=spawnSync('node',[new URL('../tools/validate_session_chain.mjs',import.meta.url).pathname,session,chain]);
assert.notEqual(bad.status,0);
console.log('v2.4 session privacy/persistence/hash-chain tests passed');
