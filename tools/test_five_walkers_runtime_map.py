from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
g=json.loads((root/'web/custom_map_graph.json').read_text(encoding='utf-8'))
adj={}
for e in g['edges']: adj.setdefault(e['from'],{})[e['direction']]=e['to']
route=[('south','/custom/oldpine/room/path02'),('southeast','/custom/oldpine/room/path03'),('southeast','/custom/oldpine/room/path04'),('northeast','/custom/oldpine/room/path05'),('north','/custom/oldpine/room/path06'),('northeast','/custom/oldpine/room/path07'),('east','/custom/oldpine/room/path08'),('east','/custom/oldpine/room/path09'),('east','/custom/oldpine/room/path10')]
start='/custom/oldpine/room/path01'; passes=[]
for w in range(1,6):
  for lap in range(1,4):
    cur=start
    for d,want in route:
      got=adj.get(cur,{}).get(d)
      if got!=want: raise SystemExit(f'walker{w} lap{lap}: {cur} {d}: {got} != {want}')
      cur=got
    # walk back using opposite exits from path10 to sgate
    rev={'east':'west','west':'east','north':'south','south':'north','northeast':'southwest','southwest':'northeast','northwest':'southeast','southeast':'northwest'}
    for d,want in reversed(route):
      back=rev[d]; prev=start if route.index((d,want))==0 else route[route.index((d,want))-1][1]
      got=adj.get(cur,{}).get(back)
      if got!=prev: raise SystemExit(f'walker{w} lap{lap} return: {cur} {back}: {got} != {prev}')
      cur=got
    passes.append({'walker':w,'lap':lap})
report={'kind':'source-derived virtual walker; NOT live Neolith/TELNET','walkers':5,'laps_each':3,'directional_transitions':len(passes)*18,'passed':True}
(root/'reports/five_walkers_runtime_map_v32027.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,ensure_ascii=False))
