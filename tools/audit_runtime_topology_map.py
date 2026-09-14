from pathlib import Path
root=Path(__file__).resolve().parents[1]
hud=(root/'source/upstream/mudlib/cmds/usr/webhud.c').read_text()
app=(root/'web/app.js').read_text()
checks={
'webhud emits exact room': '@@WEBHUD|ROOM|%s|%s' in hud,
'webhud reads LPC exits': 'query("exits")' in hud,
'webhud emits exit path': '@@WEBHUD|EXIT|%s|%s|%s' in hud,
'frontend parses exit': "a[1]==='EXIT'" in app,
'frontend accepts unknown runtime rooms': 'function ensureRuntimeRoom' in app,
'frontend merges runtime exits': 'function mergeRuntimeExit' in app,
'current room remains topology anchor': 'positions=new Map([[currentRoomId,[0,0,0]]])' in app,
}
for k,v in checks.items(): print(('PASS' if v else 'FAIL'),k)
raise SystemExit(0 if all(checks.values()) else 1)
