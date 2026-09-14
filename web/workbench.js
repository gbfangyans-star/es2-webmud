const $=s=>document.querySelector(s);let wb=null,selected=null;
const esc=s=>String(s??'').replace(/[&<>\"]/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','\"':'&quot;'}[c]));
function titleOf(x){return x.short||x.name||(x.ids||[])[0]||x.path}
function metric(k,v){return `<div class="metric"><b>${esc(v)}</b><span>${esc(k)}</span></div>`}
async function load(){
  const r=await fetch('/api/catalog?file=content_workbench.json');
  if(!r.ok){$('#summary').innerHTML='<span class="err">尚未建立 content_workbench.json。請執行 CHECK_CONTENT_WORKBENCH.bat。</span>';return}
  wb=await r.json();
  const s=wb.summary||{};$('#summary').innerHTML=[metric('索引實體',s.entities||0),metric('manual_review',s.manualReviewEntities||0),metric('triage',s.triageEntries||0),metric('關聯實體',s.relationEntities||0)].join('');
  const reasons=Object.keys(s.manualReviewReasons||{});$('#reason').innerHTML='<option value="">全部原因</option>'+reasons.map(x=>`<option>${esc(x)}</option>`).join('');
  const types=Object.keys(s.types||{});$('#type').innerHTML='<option value="">全部分類</option>'+types.map(x=>`<option>${esc(x)}</option>`).join('');
  renderReview();renderTriage();renderHotspots();
}
function renderReview(){if(!wb)return;const q=$('#q').value.trim().toLowerCase(),reason=$('#reason').value,type=$('#type').value;const rows=(wb.manualReview||[]).filter(x=>(!reason||x.reasons.includes(reason))&&(!type||x.type===type)&&(!q||JSON.stringify([x.path,x.file,x.short,x.name,x.ids]).toLowerCase().includes(q)));$('#reviewCount').textContent=`${rows.length} 筆`;$('#reviewList').innerHTML='';for(const x of rows.slice(0,500)){const b=document.createElement('button');b.className='queue-item';b.innerHTML=`<b>${esc(titleOf(x))}</b><small>${esc(x.type)} · ${esc(x.path)}</small><span>${x.reasons.map(r=>`<i>${esc(r)}</i>`).join('')}</span>`;b.onclick=()=>selectEntity(x.path);$('#reviewList').appendChild(b)}}
async function selectEntity(path){
  const [er,rr]=await Promise.all([fetch('/api/entity?path='+encodeURIComponent(path)),fetch('/api/relations?path='+encodeURIComponent(path))]);
  if(!er.ok)return;selected=await er.json();const rel=rr.ok?await rr.json():{incoming:[],outgoing:[]};const sr=await fetch('/api/source?path='+encodeURIComponent('mudlib/'+selected.file));$('#entityMeta').textContent=JSON.stringify({path:selected.path,type:selected.type,file:selected.file,manual_review:selected.manual_review||[],sha256:selected.sha256},null,2);
  $('#relations').innerHTML=[...(rel.outgoing||[]).slice(0,30).map(x=>`<button class="relation relnav" data-path="${esc(x.to)}">→ ${esc(x.kind)} · ${esc(x.to)}</button>`),...(rel.incoming||[]).slice(0,30).map(x=>`<button class="relation relnav" data-path="${esc(x.from)}">← ${esc(x.kind)} · ${esc(x.from)}</button>`)].join('');
  $('#relations').querySelectorAll('[data-path]').forEach(b=>b.onclick=()=>selectEntity(b.dataset.path));$('#sourcePreview').textContent=sr.ok?await sr.text():'[source unavailable]';$('#openEditor').disabled=false;$('#openExplorer').disabled=false;
}

function renderTriage(){const xs=(wb.triageTop||[]).slice(0,40);$('#triage').innerHTML=xs.map(x=>`<button class="queue-item" data-path="${esc(x.path)}"><b>${esc(x.path)}</b><small>score ${esc(x.score)}</small></button>`).join('');$('#triage').querySelectorAll('[data-path]').forEach(b=>b.onclick=()=>selectEntity(b.dataset.path))}
function renderHotspots(){const xs=(wb.dependencyHotspots||[]).slice(0,40);$('#hotspots').innerHTML=xs.map(x=>`<button class="queue-item" data-path="${esc(x.path)}"><b>${esc(x.path)}</b><small>incoming ${x.incoming} · outgoing ${x.outgoing} · degree ${x.degree}</small></button>`).join('');$('#hotspots').querySelectorAll('[data-path]').forEach(b=>b.onclick=()=>selectEntity(b.dataset.path))}
$('#reload').onclick=load;$('#reason').onchange=renderReview;$('#type').onchange=renderReview;$('#q').oninput=renderReview;$('#openEditor').onclick=()=>{if(selected)location.href='/admin.html?path='+encodeURIComponent(selected.path)};$('#openExplorer').onclick=()=>{if(selected)location.href='/explorer.html?q='+encodeURIComponent(selected.path)};load();
