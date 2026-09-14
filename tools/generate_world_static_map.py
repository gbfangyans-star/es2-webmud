from pathlib import Path
import re, json

root=Path(__file__).resolve().parents[1]
mud=root/'source/upstream/mudlib'
roots=[mud/'d', mud/'custom']
room_paths=[]
for base in roots:
    if not base.exists(): continue
    for p in sorted(base.rglob('*.c')):
        txt=p.read_text(encoding='utf-8',errors='ignore')
        if 'inherit ROOM' in txt or '/std/room' in txt:
            room_paths.append(p)

nodes=[]; room_ids=set()
for p in room_paths:
    rid='/' + p.relative_to(mud).with_suffix('').as_posix()
    txt=p.read_text(encoding='utf-8',errors='ignore')
    m=re.search(r'set\(\s*"short"\s*,\s*"([^"]*)"\s*\)',txt)
    label=m.group(1).strip() if m else p.stem
    nodes.append({'id':rid,'label':label})
    room_ids.add(rid)

DIRS=r'(north|south|east|west|northeast|northwest|southeast|southwest|up|down|enter|out)'
edges=[]
for p in room_paths:
    rid='/' + p.relative_to(mud).with_suffix('').as_posix()
    txt=p.read_text(encoding='utf-8',errors='ignore')
    roomdir='/' + p.parent.relative_to(mud).as_posix() + '/'
    # absolute literal destinations
    for d,to in re.findall(r'"'+DIRS+r'"\s*:\s*"(/[^"#]+)(?:#\d+)?"',txt):
        edges.append({'from':rid,'to':to.rstrip('/'),'direction':d,'resolved':to.rstrip('/') in room_ids})
    # __DIR__ destinations
    for d,name in re.findall(r'"'+DIRS+r'"\s*:\s*__DIR__\s*"([^"]+)"',txt):
        to=(roomdir+name).replace('//','/').rstrip('/')
        edges.append({'from':rid,'to':to,'direction':d,'resolved':to in room_ids})

seen=set(); dedup=[]
for e in edges:
    k=(e['from'],e['direction'],e['to'])
    if k in seen: continue
    seen.add(k); dedup.append(e)

# Keep only destinations represented by rooms in the static map. Runtime HUD can still
# expose a transition to a dynamic/unindexed room without changing the fixed layout.
dedup=[e for e in dedup if e['to'] in room_ids]

out={
  'format':'es2-static-world-map-v1',
  'generated_from':['source/upstream/mudlib/d/**/*.c','source/upstream/mudlib/custom/**/*.c'],
  'layout_policy':'fixed topology; player position only moves by room path',
  'nodes':nodes,
  'edges':dedup,
}
(root/'web/world_static_map.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(f"generated {len(nodes)} rooms, {len(dedup)} exits")
