from pathlib import Path
p=Path(__file__).resolve().parents[1]
app=(p/'web/app.js').read_text(encoding='utf-8')
checks={
 'room_starts_snapshot': "beginRuntimeRoomSnapshot(a[2]" in app,
 'snapshot_clears_outgoing': 'adjacency.set(id,[]);' in app,
 'runtime_exit_rebuilds': 'mergeRuntimeExit(a[2],a[3],a[4])' in app,
 'no_ambiguous_first_guess': 'if(candidates.length===1)return candidates[0]' in app and 'candidates.find(id=>near.has(id))' in app,
}
for k,v in checks.items(): print(('PASS' if v else 'FAIL'),k)
raise SystemExit(0 if all(checks.values()) else 1)
