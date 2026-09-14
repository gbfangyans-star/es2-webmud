import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';
import {PlayerStateObserver} from '../web/player_state.js';

const o=new PlayerStateObserver();
o.consume('你的眼前一黑，接著什麼也不知道了....\n');
o.consume('慢慢地你終於又有了知覺....\n');
o.consume('你死了！！\n');
o.consume('重新連線完畢。\n');
const kinds=o.state.events.map(e=>e.kind);
assert.ok(kinds.includes('unconscious_self_exact'));
assert.ok(kinds.includes('revive_self_exact'));
assert.ok(kinds.includes('death_self_exact'));
assert.ok(kinds.includes('reconnect_complete_exact'));

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v19-'));
const replay=path.join(dir,'replay.json'),matrix=path.join(dir,'matrix.json'),movement=path.join(dir,'movement.json');
fs.writeFileSync(replay,JSON.stringify({
  coverage:{score:true,hp:true,skills:true,inventory:true,look:true,movement:true},
  observations:{events:[
    {kind:'combat_text'},{kind:'unconscious_self_exact'},{kind:'revive_self_exact'},
    {kind:'death_self_exact'},{kind:'reconnect_complete_exact'}
  ]}
}));

// Current contract: movement command coverage alone is not acceptance.
execFileSync('node',[new URL('../tools/build_acceptance_matrix.mjs',import.meta.url).pathname,'--replay',replay,'--out',matrix],{stdio:'pipe'});
let x=JSON.parse(fs.readFileSync(matrix,'utf8'));
assert.equal(x.checks.movement.pass,false);
assert.equal(x.complete,false);

// Strong movement evidence upgrades the matrix.
fs.writeFileSync(movement,JSON.stringify({ok:true}));
execFileSync('node',[new URL('../tools/build_acceptance_matrix.mjs',import.meta.url).pathname,'--replay',replay,'--movement',movement,'--out',matrix],{stdio:'pipe'});
x=JSON.parse(fs.readFileSync(matrix,'utf8'));
assert.equal(x.complete,true);
execFileSync('node',[new URL('../tools/final_runtime_gate.mjs',import.meta.url).pathname,matrix],{stdio:'pipe'});

x.checks.death.pass=false;x.complete=false;fs.writeFileSync(matrix,JSON.stringify(x));
const bad=spawnSync('node',[new URL('../tools/final_runtime_gate.mjs',import.meta.url).pathname,matrix]);
assert.notEqual(bad.status,0);
console.log('current lifecycle/reconnect + strong movement acceptance tests passed');
