import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync} from 'node:child_process';
import {SessionRecorder} from '../web/session_recorder.js';

const r=new SessionRecorder();
r.beginCommand('score');r.appendResponse('目前是等級 1 的平民，累積業力共 0 點。\\n');r.finishResponse();
r.beginCommand('hp');r.appendResponse('形體 10/10\\n');r.finishResponse();
r.beginCommand('skills');r.appendResponse('基本內功 (force) - 初學乍練 1\\n');r.finishResponse();
r.beginCommand('inventory');r.appendResponse('你身上沒有任何東西\\n');r.finishResponse();
r.beginCommand('look');r.appendResponse('房間原生輸出\\n');r.finishResponse();
r.beginCommand('go north');r.appendResponse('這個方向沒有出路。\\n');r.finishResponse();
assert.equal(r.manifest().records,6);
assert.equal(r.manifest().coverage.movement,true);

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v18-'));
const session=path.join(dir,'session.jsonl'),ev=path.join(dir,'evidence.json');
fs.writeFileSync(session,r.toJSONL());
execFileSync('node',[new URL('../tools/build_session_evidence.mjs',import.meta.url).pathname,'--session',session,'--out',ev],{stdio:'pipe'});
const x=JSON.parse(fs.readFileSync(ev,'utf8'));
assert.equal(x.coverage.score,true);
assert.equal(x.coverage.movement,true);
execFileSync('node',[new URL('../tools/session_coverage_gate.mjs',import.meta.url).pathname,ev],{stdio:'pipe'});
console.log('v1.8 browser session capture tests passed');
