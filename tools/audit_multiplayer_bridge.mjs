#!/usr/bin/env node
import fs from 'node:fs';
const p=process.argv[2];
if(!p){console.error('usage: audit_multiplayer_bridge.mjs server/index.js');process.exit(2)}
const t=fs.readFileSync(p,'utf8');
const ws=t.indexOf("wss.on('connection'");
const tcp=t.indexOf('net.createConnection',ws);
const handlerEnd=t.indexOf("const ping=setInterval",ws);
const checks={
  ws_connection_handler:ws>=0,
  tcp_created_inside_ws_handler:ws>=0&&tcp>ws&&(handlerEnd<0||tcp<handlerEnd),
  per_session_id:t.includes('const id=++sessionSeq'),
  session_map:t.includes('sessions.set(id'),
  ws_close_destroys_tcp:t.includes("ws.on('close'")&&t.includes('tcp.destroy()'),
  tcp_close_removes_session:t.includes("tcp.on('close'")&&t.includes('sessions.delete(id)')
};
const out={ok:Object.values(checks).every(Boolean),checks,
  meaning:'Structural audit only. Live multiplayer gameplay still requires concurrent player testing.'};
console.log(JSON.stringify(out,null,2));
process.exit(out.ok?0:2);
