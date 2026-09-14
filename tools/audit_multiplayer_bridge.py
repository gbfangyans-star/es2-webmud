#!/usr/bin/env python3
from pathlib import Path
import argparse,json,re
ap=argparse.ArgumentParser();ap.add_argument("server_file");a=ap.parse_args()
t=Path(a.server_file).read_text(encoding="utf-8")
checks={
 "ws_connection_handler": "wss.on('connection'" in t,
 "tcp_created_inside_ws_handler": bool(re.search(r"wss\.on\('connection'.*?net\.createConnection",t,re.S)),
 "per_session_id": "const id=++sessionSeq" in t,
 "session_map": "sessions.set(id" in t,
 "ws_close_destroys_tcp": "ws.on('close'" in t and "tcp.destroy()" in t,
 "tcp_close_removes_session": "tcp.on('close'" in t and "sessions.delete(id)" in t
}
out={"ok":all(checks.values()),"checks":checks,
"meaning":"Structural audit only. Real multiplayer correctness still requires live concurrent-player testing."}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
