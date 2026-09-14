import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';

const root=new URL('../',import.meta.url).pathname;
const audit=new URL('../tools/audit_multiplayer_bridge.mjs',import.meta.url).pathname;
const server=new URL('../server/index.js',import.meta.url).pathname;
const out=execFileSync('node',[audit,server],{encoding:'utf8'});
const x=JSON.parse(out);
assert.equal(x.ok,true);
assert.equal(x.checks.tcp_created_inside_ws_handler,true);

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v22-'));
const fake=path.join(dir,'bad.js');
fs.writeFileSync(fake,"const x='no websocket bridge';");
const bad=spawnSync('node',[audit,fake],{encoding:'utf8'});
assert.notEqual(bad.status,0);
console.log('v2.2 multiplayer audit regression passed');
