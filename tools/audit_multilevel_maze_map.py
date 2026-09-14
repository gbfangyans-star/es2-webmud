#!/usr/bin/env python3
from pathlib import Path
r=Path(__file__).resolve().parents[1]
a=(r/'web/app.js').read_text()
h=(r/'source/upstream/mudlib/cmds/usr/webhud.c').read_text()
i=(r/'web/index.html').read_text()
checks={
 'webhud map metadata':'@@WEBHUD|MAPMETA|' in h,
 'area property':'map/area' in h,
 'layer property':'map/layer' in h,
 'mode property':'map/mode' in h,
 'maze hides unknown':"cell.textContent='？？？'" in a,
 'maze reset invalidates exploration':'old!==now' in a and 'exploredRooms.clear()' in a,
 'vertical transitions':"e.direction==='up'?'▲'" in a and "e.direction==='down'?'▼'" in a,
 'cross layer filter':'sameMapLayer' in a,
 'layer hud':'mapLayerHud' in i and 'mapLayerHud' in a,
 'transition hud':'mapTransitions' in i and 'mapTransitions' in a,
}
for k,v in checks.items(): print(('PASS' if v else 'FAIL'),k)
raise SystemExit(0 if all(checks.values()) else 1)
