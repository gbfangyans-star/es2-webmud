const $=s=>document.querySelector(s);
async function text(r){const t=await r.text();try{return JSON.stringify(JSON.parse(t),null,2)}catch{return t}}
$('#verify').onclick=async()=>$('#oplog').textContent=await text(await fetch('/api/admin/verify-source'));
$('#reindex').onclick=async()=>{$('#oplog').textContent='執行中…';$('#oplog').textContent=await text(await fetch('/api/admin/reindex',{method:'POST'}))};
async function load(){const r=await fetch('/api/admin/backups');if(!r.ok){$('#backups').textContent=await r.text();return}const a=await r.json();$('#backups').innerHTML='';for(const x of a){const b=document.createElement('button');b.className='roomitem';b.textContent=x.path+' · '+x.bytes+' bytes';b.onclick=()=>$('#backup').value=x.path;$('#backups').appendChild(b)}}
$('#reload').onclick=load;
$('#diff').onclick=async()=>{$('#diffout').textContent=await text(await fetch('/api/admin/backup-diff?backup='+encodeURIComponent($('#backup').value)+'&current='+encodeURIComponent($('#current').value)))};
$('#restore').onclick=async()=>{if(!confirm('確定用此備份覆蓋目前 LPC？'))return;$('#diffout').textContent=await text(await fetch('/api/admin/restore',{method:'POST',headers:{'content-type':'application/json'},body:JSON.stringify({backup:$('#backup').value,current:$('#current').value})}))};
load();