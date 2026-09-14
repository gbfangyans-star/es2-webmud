import json, hashlib, collections, pathlib
root=pathlib.Path('/mnt/data/map_v7_work')
p=root/'web/world_static_map.json'
d=json.loads(p.read_text(encoding='utf-8'))
vec={'north':(0,-1),'south':(0,1),'east':(1,0),'west':(-1,0),'northeast':(1,-1),'northwest':(-1,-1),'southeast':(1,1),'southwest':(-1,1)}
nodes={n['id']:n for n in d['nodes']}
adj={i:[] for i in nodes}
for e in d['edges']:
    if e.get('resolved') and e.get('from') in nodes and e.get('to') in nodes:
        adj[e['from']].append(e)
# exact port of V6 deterministic stable position builder, frozen into DB
pos={}; occupied=set(); component=0
for seed in sorted(nodes):
    if seed in pos: continue
    bx,by=component*20,0; component+=1
    pos[seed]=(bx,by); occupied.add((bx,by)); q=collections.deque([seed])
    while q:
        fr=q.popleft(); px,py=pos[fr]
        for e in adj[fr]:
            v=vec.get(str(e.get('direction','')).lower()); to=e['to']
            if not v or to in pos: continue
            nx,ny=px+v[0],py+v[1]; tries=0
            while (nx,ny) in occupied and tries<12:
                nx += v[1] or 1
                ny -= v[0] or 0
                tries += 1
            pos[to]=(nx,ny); occupied.add((nx,ny)); q.append(to)
for n in d['nodes']:
    n['x'],n['y']=pos[n['id']]
# audit directional inconsistencies after freezing coords
conf=[]
for e in d['edges']:
    if not e.get('resolved') or e.get('from') not in pos or e.get('to') not in pos: continue
    v=vec.get(str(e.get('direction','')).lower())
    if not v: continue
    a=pos[e['from']]; b=pos[e['to']]
    expected=(a[0]+v[0], a[1]+v[1])
    if b != expected:
        conf.append({'from':e['from'],'to':e['to'],'direction':e['direction'],'from_xy':a,'to_xy':b,'expected_to_xy':expected})
d['format']='es2-static-world-map-v2-readonly-coordinates'
d['layout_policy']='authoritative immutable topology and coordinates; runtime may update player position/exploration only'
d['coordinate_policy']='precomputed at build time from LPC exits; browser must never recalculate or mutate coordinates'
d['nodes']=sorted(d['nodes'],key=lambda n:n['id'])
p.write_text(json.dumps(d,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
report={
 'nodes':len(d['nodes']),'edges':len(d['edges']),'components':component,
 'coordinate_conflicts':len(conf),'conflicts':conf,
 'map_sha256':hashlib.sha256(p.read_bytes()).hexdigest()
}
(root/'reports').mkdir(exist_ok=True)
(root/'reports/MAP_V7_READONLY_COORDINATE_AUDIT.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps({k:v for k,v in report.items() if k!='conflicts'},ensure_ascii=False))
for c in conf[:20]: print(c)
