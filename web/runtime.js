const $=s=>document.querySelector(s);
async function show(url,opts){$('#out').textContent='執行中…';const r=await fetch(url,opts);const t=await r.text();try{$('#out').textContent=JSON.stringify(JSON.parse(t),null,2)}catch{$('#out').textContent=t}}
$('#readiness').onclick=()=>show('/api/runtime-readiness');
$('#probe').onclick=()=>show('/api/runtime-probe',{method:'POST'});
