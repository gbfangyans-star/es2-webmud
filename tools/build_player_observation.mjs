#!/usr/bin/env node
import fs from 'node:fs';
import crypto from 'node:crypto';
import {PlayerStateObserver} from '../web/player_state.js';
const args=process.argv.slice(2);const opt={};
for(let i=0;i<args.length;i+=2)opt[args[i].replace(/^--/,'')]=args[i+1];
for(const k of ['hp','skills','inventory','out']){if(!opt[k]){console.error(`missing --${k}`);process.exit(2)}}
const result={format:'es2-player-observation-v1',source:'canonical command transcripts',commands:{}};
for(const mode of ['hp','skills','inventory']){
  const text=fs.readFileSync(opt[mode],'utf8');const o=new PlayerStateObserver();o.begin(mode);o.consume(text);
  result.commands[mode]={sha256:crypto.createHash('sha256').update(text).digest('hex'),state:o.state};
}
fs.writeFileSync(opt.out,JSON.stringify(result,null,2));
console.log(JSON.stringify({ok:true,out:opt.out,commands:Object.keys(result.commands)},null,2));
