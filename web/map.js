const $=s=>document.querySelector(s),svg=$('#map'),NS='http://www.w3.org/2000/svg';
const vec={north:[0,-1],south:[0,1],east:[1,0],west:[-1,0],northeast:[1,-1],northwest:[-1,-1],southeast:[1,1],southwest:[-1,1],up:[0,-1],down:[0,1]};
function E(tag,attrs={}){const e=document.createElementNS(NS,tag);for(const [k,v] of Object.entries(attrs))e.setAttribute(k,v);return e}
function resolve(owner,target,relative){if(!relative)return target.startsWith('/')?target:'/'+target;const parts=owner.split('/');parts.pop();for(const s of target.split('/')){if(!s||s=='.')continue;if(s=='..')parts.pop();else parts.push(s)}return parts.join('/')||'/'}
async function draw(){let data;try{data=await fetch('/api/catalog?file=world_graph.json').then(r=>{if(!r.ok)throw Error('尚未建立 world_graph.json');return r.json()})}catch(e){$('#mapinfo').textContent=e.message;return}
const pre=$('#prefix').value.trim(),nodes=data.nodes.filter(n=>!pre||n.id.startsWith(pre)),set=new Set(nodes.map(n=>n.id));const edges=data.edges.filter(e=>set.has(e.from)&&set.has(e.to));
const pos=new Map(),adj=new Map();for(const n of nodes)adj.set(n.id,[]);for(const e of edges){adj.get(e.from)?.push(e)}
let component=0;for(const n of nodes){if(pos.has(n.id))continue;const baseX=component*8;baseY=0;pos.set(n.id,[baseX,baseY]);const q=[n.id];while(q.length){const id=q.shift(),[x,y]=pos.get(id);for(const e of adj.get(id)||[]){if(pos.has(e.to))continue;const v=vec[e.direction];if(v){pos.set(e.to,[x+v[0],y+v[1]]);q.push(e.to)}}}component++}
// spread collisions deterministically for display only
const occupied=new Map();for(const [id,p] of pos){const k=p.join(',');const c=occupied.get(k)||0;occupied.set(k,c+1);if(c)p[0]+=c*.28}
if(!pos.size){$('#mapinfo').textContent='沒有符合的 room';svg.replaceChildren();return}
let xs=[...pos.values()].map(p=>p[0]),ys=[...pos.values()].map(p=>p[1]);const minx=Math.min(...xs),maxx=Math.max(...xs),miny=Math.min(...ys),maxy=Math.max(...ys),S=130,M=80,W=(maxx-minx+1)*S+M*2,H=(maxy-miny+1)*S+M*2;svg.setAttribute('viewBox',`0 0 ${W} ${H}`);svg.replaceChildren();
const xy=id=>{const [x,y]=pos.get(id);return [M+(x-minx)*S,M+(y-miny)*S]};
for(const e of edges){if(!pos.has(e.from)||!pos.has(e.to))continue;const [x1,y1]=xy(e.from),[x2,y2]=xy(e.to),line=E('line',{x1,y1,x2,y2,class:'mapedge'});svg.append(line);const t=E('text',{x:(x1+x2)/2+4,y:(y1+y2)/2-4,class:'mapdir'});t.textContent=e.direction;svg.append(t)}
for(const n of nodes){if(!pos.has(n.id))continue;const [x,y]=xy(n.id),g=E('g',{class:'mapnode'}),r=E('rect',{x:x-48,y:y-24,width:96,height:48,rx:7});const t=E('text',{x,y:y-2,'text-anchor':'middle'});t.textContent=(n.label||n.id).slice(0,12);const p=E('text',{x,y:y+15,'text-anchor':'middle',class:'mappath'});p.textContent=n.id.split('/').pop();g.append(r,t,p);g.onclick=()=>location.href='/explorer.html?q='+encodeURIComponent(n.id);svg.append(g)}
$('#mapinfo').textContent=`${nodes.length} rooms · ${edges.length} resolved edges`}
$('#draw').onclick=draw;draw();
