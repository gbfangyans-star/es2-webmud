const $=s=>document.querySelector(s);let current=null;
const esc=s=>String(s).replace(/[&<>\"]/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','\"':'&quot;'}[c]));
async function search(){const q=$('#q').value.trim(),type=$('#type').value;const ps=new URLSearchParams();if(q)ps.set('q',q);if(type)ps.set('type',type);if(!q&&!type)ps.set('q','/');const r=await fetch('/api/search?'+ps);if(!r.ok){$('#count').textContent=await r.text();return}const data=await r.json();$('#count').textContent=`顯示 ${data.count} 筆（最多 500）`;$('#results').innerHTML='';for(const x of data.results){const b=document.createElement('button');b.className='roomitem';b.innerHTML=`<b>${esc(x.short||x.name||x.command||x.path)}</b><br><small>${esc(x.type)} · ${esc(x.path)}</small>`;b.onclick=()=>show(x);$('#results').appendChild(b)}}
function rels(x){const a=[];for(const [d,e] of Object.entries(x.exits||{}))a.push(`${d} → ${e.relative?'[relative] ':''}${e.target}`);for(const o of x.objects||[])a.push(`object → ${o.relative?'[relative] ':''}${o.target} ×${o.count}`);for(const m of x.merchandise||[])a.push(`merchandise → ${m.relative?'[relative] ':''}${m.target} ×${m.stock}`);for(const e of x.equipment||[])a.push(`equipment → ${e.target||e.stock_type+':'+e.name}`);for(const s of x.skills||[])a.push(`skill → ${s.skill} ${s.level}`);for(const m of x.skill_maps||[])a.push(`map_skill → ${m.base} => ${m.mapped_to}`);return a}
async function show(x){
  current=x;$('#detail').textContent=JSON.stringify(x,null,2);
  const local=rels(x);let rel={incoming:[],outgoing:[]};
  try{rel=await fetch('/api/relations?path='+encodeURIComponent(x.path)).then(r=>r.json())}catch{}
  const nav=[];
  for(const y of rel.outgoing||[])nav.push(`<button class="relation relbtn" data-path="${esc(y.to)}">→ ${esc(y.kind)} · ${esc(y.to)}</button>`);
  for(const y of rel.incoming||[])nav.push(`<button class="relation relbtn" data-path="${esc(y.from)}">← ${esc(y.kind)} · ${esc(y.from)}</button>`);
  $('#linksCard').hidden=!(local.length||nav.length);
  $('#links').innerHTML=local.map(v=>`<div class="relation">${esc(v)}</div>`).join('')+nav.join('');
  $('#links').querySelectorAll('[data-path]').forEach(b=>b.onclick=async()=>{
    const r=await fetch('/api/entity?path='+encodeURIComponent(b.dataset.path));
    if(r.ok)show(await r.json())
  });
}
const initial=new URLSearchParams(location.search);if(initial.get('q'))$('#q').value=initial.get('q');if(initial.get('type'))$('#type').value=initial.get('type');$('#go').onclick=search;$('#q').onkeydown=e=>{if(e.key==='Enter')search()};$('#type').onchange=search;search();
