const $=s=>document.querySelector(s);let rows=[],kind='npc';
const esc=s=>String(s??'').replace(/[&<>"]/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;'}[c]));
async function load(k){kind=k;const r=await fetch('/api/index?kind='+encodeURIComponent(k));rows=r.ok?await r.json():[];render()}
function label(x){return x.name||x.command||x.path||'(unnamed)'}
function render(){const q=$('#filter').value.trim().toLowerCase();$('#list').innerHTML='';for(const x of rows.filter(x=>!q||JSON.stringify(x).toLowerCase().includes(q)).slice(0,2000)){const b=document.createElement('button');b.className='roomitem';b.innerHTML=`<b>${esc(label(x))}</b><br><small>${esc(x.path||'')}</small>`;b.onclick=()=>show(x);$('#list').appendChild(b)}}
async function show(x){$('#title').textContent=label(x);$('#detail').textContent=JSON.stringify(x,null,2)}
document.querySelectorAll('[data-kind]').forEach(b=>b.onclick=()=>load(b.dataset.kind));$('#filter').oninput=render;load('npc');