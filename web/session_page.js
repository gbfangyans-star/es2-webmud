import {SessionRecorder} from './session_recorder.js';
const rec=window.__es2SessionRecorder || new SessionRecorder();
window.__es2SessionRecorder=rec;
const $=s=>document.querySelector(s);
function dl(name,text,type='text/plain'){
  const a=document.createElement('a');
  a.href=URL.createObjectURL(new Blob([text],{type}));
  a.download=name;a.click();setTimeout(()=>URL.revokeObjectURL(a.href),500);
}
function render(){
  const m=rec.manifest();
  $('#summary').textContent=JSON.stringify(m,null,2);
  $('#coverage').innerHTML=Object.entries(m.coverage).map(([k,v])=>`<div class="relation"><b>${k}</b> ${v?'✓':'·'}</div>`).join('');
}
$('#exportJsonl').onclick=()=>dl('es2-session.jsonl',rec.toJSONL(),'application/x-ndjson');
$('#exportManifest').onclick=()=>dl('es2-session-manifest.json',JSON.stringify(rec.manifest(),null,2),'application/json');
$('#clear').onclick=()=>{rec.reset();render()};
setInterval(render,1000);render();
