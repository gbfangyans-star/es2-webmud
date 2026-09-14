#!/usr/bin/env node
import fs from 'node:fs';
import {PlayerStateObserver} from '../web/player_state.js';
const [,,file,mode='score']=process.argv;
if(!file){console.error('usage: node tools/parse_player_transcript.mjs <file> [score|hp|skills|inventory]');process.exit(2)}
const o=new PlayerStateObserver();o.begin(mode);o.consume(fs.readFileSync(file,'utf8'));
console.log(JSON.stringify({mode,state:o.state},null,2));
