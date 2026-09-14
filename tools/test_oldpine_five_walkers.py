from pathlib import Path
import re, json
root=Path(__file__).resolve().parents[1]
rooms=root/'source/upstream/mudlib/custom/oldpine/room'
# Current user-supplied Gao Shen route only. This is a source-level fallback test,
# NOT a substitute for live Neolith/TELNET player testing.
files={p.stem:p for p in rooms.glob('path*.c')}
exits={}
for name,p in files.items():
    s=p.read_text()
    exits[name]={d:t for d,t in re.findall(r'"(north|south|east|west|northeast|northwest|southeast|southwest)"\s*:\s*__DIR__"(path\d+)"',s)}
route=['path01','path02','path03','path04','path05','path06','path07','path08','path09','path10']
# expected forward directions from the currently shipped map
forward=['south','southeast','southeast','northeast','north','northeast','east','east','east']
reverse={'north':'south','south':'north','east':'west','west':'east','northeast':'southwest','northwest':'southeast','southeast':'northwest','southwest':'northeast'}
results=[]
for player in range(1,6):
    ok=True; traversals=0
    for lap in range(3):
        cur=route[0]
        for i,d in enumerate(forward):
            nxt=exits.get(cur,{}).get(d); ok &= nxt==route[i+1]; cur=nxt; traversals+=1
        for i in range(len(forward)-1,-1,-1):
            d=reverse[forward[i]]; nxt=exits.get(cur,{}).get(d); ok &= nxt==route[i]; cur=nxt; traversals+=1
    results.append({'player':player,'laps':3,'directional_transitions':traversals,'passed':bool(ok)})
out={'mode':'source_level_fallback_NOT_live_neolith','players':results,'all_passed':all(x['passed'] for x in results)}
(root/'reports/oldpine_five_walker_source_test.json').write_text(json.dumps(out,ensure_ascii=False,indent=2))
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out['all_passed'] else 1)
