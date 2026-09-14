#!/usr/bin/env node
import fs from 'node:fs';

const args=process.argv.slice(2),opt={};
for(let i=0;i<args.length;i+=2) opt[args[i].replace(/^--/,'')]=args[i+1];
if(!opt.replay||!opt.out){
  console.error('usage: build_acceptance_matrix.mjs --replay report.json --out matrix.json [--movement movement.json]');
  process.exit(2);
}
const x=JSON.parse(fs.readFileSync(opt.replay,'utf8'));
const events=x.observations?.events||[];
const kinds=new Set(events.map(e=>e.kind));
const cov=x.coverage||{};
let movementPass=false,movementEvidence='strong movement transition evidence not supplied';
if(opt.movement){
  try{
    const m=JSON.parse(fs.readFileSync(opt.movement,'utf8'));
    movementPass=!!m.ok;
    movementEvidence=movementPass?'look-before/go/look-after transition verified':'movement transition verifier did not pass';
  }catch{movementEvidence='movement evidence invalid'}
}
const matrix={
  format:'es2-runtime-acceptance-v2',
  checks:{
    score:{pass:!!cov.score,evidence:'captured command coverage'},
    hp:{pass:!!cov.hp,evidence:'captured command coverage'},
    skills:{pass:!!cov.skills,evidence:'captured command coverage'},
    inventory:{pass:!!cov.inventory,evidence:'captured command coverage'},
    look:{pass:!!cov.look,evidence:'captured command coverage'},
    movement:{pass:movementPass,evidence:movementEvidence},
    combat:{pass:kinds.has('fight_won_exact')||kinds.has('fight_lost_exact')||kinds.has('combat_text'),evidence:'observed combat output'},
    unconscious:{pass:kinds.has('unconscious_self_exact'),evidence:'exact std/char.c self message'},
    revive:{pass:kinds.has('revive_self_exact'),evidence:'exact std/char.c self message'},
    death:{pass:kinds.has('death_self_exact')||kinds.has('ghost_destroyed_exact'),evidence:'exact std/char.c self message'},
    reconnect:{pass:kinds.has('reconnect_complete_exact'),evidence:'exact obj/user.c reconnect message'}
  },
  notes:[
    'Command coverage proves only that the command was captured.',
    'Movement PASS requires a captured before-look/go/after-look transition and no canonical go failure.',
    'Combat/lifecycle/reconnect exact passes require canonical observed output.'
  ]
};
matrix.complete=Object.values(matrix.checks).every(v=>v.pass);
fs.writeFileSync(opt.out,JSON.stringify(matrix,null,2));
console.log(JSON.stringify({ok:true,complete:matrix.complete,out:opt.out},null,2));
