from pathlib import Path
import re,json
root=Path(__file__).resolve().parents[1]
mud=root/'source/upstream/mudlib'
base=mud/'custom'
rooms=[]; edges=[]
# Generic source-derived seed only. Runtime WebHUD remains authoritative.
for p in sorted(base.rglob('*.c')):
    txt=p.read_text(encoding='utf-8',errors='ignore')
    if 'inherit ROOM' not in txt and '/std/room' not in txt: continue
    rid='/' + p.relative_to(mud).with_suffix('').as_posix()
    m=re.search(r'set\("short"\s*,\s*"([^"]+)"',txt)
    label=m.group(1) if m else p.stem
    rooms.append({'id':rid,'label':label})
    # Parse literal direction -> absolute LPC destination pairs inside source.
    dirs=r'(north|south|east|west|northeast|northwest|southeast|southwest|up|down)'
    for d,to in re.findall(r'"'+dirs+r'"\s*:\s*"(/[^"]+)"',txt):
        edges.append({'from':rid,'to':to,'direction':d,'resolved':True})
    roomdir='/' + p.parent.relative_to(mud).as_posix() + '/'
    for d,name in re.findall(r'"'+dirs+r'"\s*:\s*__DIR__"([^"]+)"',txt):
        edges.append({'from':rid,'to':roomdir+name,'direction':d,'resolved':True})
# de-dupe
seen=set(); out=[]
for e in edges:
    k=(e['from'],e['direction'],e['to'])
    if k not in seen: seen.add(k);out.append(e)
data={'generated_from':'source/upstream/mudlib/custom/**/*.c','authority':'seed-only; runtime WebHUD ROOM+EXIT wins','nodes':rooms,'edges':out}
(root/'web/custom_map_graph.json').write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(f"generated {len(rooms)} rooms, {len(out)} exits")
