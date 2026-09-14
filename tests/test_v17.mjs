import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync} from 'node:child_process';
import {PlayerStateObserver} from '../web/player_state.js';

const o=new PlayerStateObserver();
o.begin('score');
o.consume('某人出生於某日，目前是等級 12 的武者，累積業力共 34 點。\n 膂力  20 (+2)   膽識  15     悟性  18 (-1)   靈性  17\n 定力  14     機敏  19     根骨  16     慧根  13\n 形體   90/ 100\n 精     80/  90\n 氣     70/  80\n 神     60/  70\n 食物   50/ 100\t\t飲水   40/ 100\t\t疲勞   30/ 100\n');
assert.equal(o.state.scoreDetail.level,12);
assert.equal(o.state.scoreDetail.karma,34);
assert.deepEqual(o.state.scoreDetail.attributes.str,{value:20,base:18,delta:2});
assert.deepEqual(o.state.scoreDetail.attributes.int,{value:18,base:19,delta:-1});
assert.deepEqual(o.state.scoreDetail.stats.hp,{current:90,maximum:100});

o.begin('go','go north'); o.consume('這個方向沒有出路。\n');
assert.equal(o.state.navigation.at(-1).kind,'no_exit');
o.begin('look'); o.consume('你現在什麼也看不到﹗\n');
assert.equal(o.state.navigation.at(-1).kind,'look_blocked');

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v17-'));
const input=path.join(dir,'session.jsonl'),out=path.join(dir,'report.json');
const records=[
 {command:'score',response:'目前是等級 1 的平民，累積業力共 0 點。\\n形體 10/10\\n'},
 {command:'hp',response:'形體 10/10\\t精 10/10\\t氣 10/10\\t神 10/10\\n食物 10/10\\t飲水 10/10\\t疲勞 0/10\\n'},
 {command:'skills',response:'基本內功 (force) - 初學乍練 1\\n'},
 {command:'inventory',response:'你身上沒有任何東西\\n'},
 {command:'look',response:'一個房間的原生輸出\\n'},
 {command:'go north',response:'這個方向沒有出路。\\n'}
];
fs.writeFileSync(input,records.map(x=>JSON.stringify(x)).join('\n'));
execFileSync('node',[new URL('../tools/replay_session.mjs',import.meta.url).pathname,'--in',input,'--out',out],{stdio:'pipe'});
const rep=JSON.parse(fs.readFileSync(out,'utf8'));
assert.equal(rep.coverage.movement,true);
assert.equal(rep.steps.length,6);
console.log('v1.7 score/navigation/session replay tests passed');
