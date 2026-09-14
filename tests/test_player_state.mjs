import assert from 'node:assert/strict';
import {PlayerStateObserver} from '../web/player_state.js';
const o=new PlayerStateObserver();
o.begin('score');o.consume('等級 5 形體 10/20 精 9/18 氣 8/17 神 7/16\n');assert.equal(o.state.score.level,5);assert.equal(o.state.score.hp,10);
o.begin('hp');o.consume('形體 10/20\t精 9/18\t氣 8/17\t神 7/16\n食物 6/100\t飲水 5/100\t疲勞 4/100\n');assert.equal(o.state.vitals.hp.current,10);assert.equal(o.state.vitals.fatigue.limit,100);
o.begin('skills');o.consume('  基本拳腳 (unarmed) - 粗通皮毛  30\n');assert.equal(o.state.skills[0].skillId,'unarmed');assert.equal(o.state.skills[0].effectiveLevel,30);
o.begin('inventory');o.consume('你身上帶著下列這些東西(負重 10%)﹕\n  石頭\n');assert.equal(o.state.inventory[0].text,'石頭');
console.log('player state observation tests passed');
