#!/bin/bash
# Start/stop the new ES2 WebMUD (wolfer168/es2-webmud) stack in WSL.
# Usage: es2webmud_ctl.sh start|stop|status
set -u
ROOT=~/es2-webmud
NEOLITH_BIN="$ROOT/source/upstream/neolith/out/build/linux/src/RelWithDebInfo/neolith"

status() {
  echo "neolith: $(pgrep -f "$NEOLITH_BIN" >/dev/null && echo running || echo stopped)  (port 4000)"
  echo "bridge : $(ss -ltn 2>/dev/null | grep -q ':8080 ' && echo running || echo stopped)  (port 8080)"
}

stop() {
  pkill -f "$NEOLITH_BIN" 2>/dev/null
  pkill -f "es2-webmud/server/index.js" 2>/dev/null
  pkill -f "node index.js" 2>/dev/null   # covers relative-path launches too
  fuser -k 8080/tcp 2>/dev/null
  fuser -k 4000/tcp 2>/dev/null
  sleep 1
  status
}

start() {
  stop
  cd "$ROOT/source/upstream" || exit 1
  setsid nohup "$NEOLITH_BIN" -f neolith.conf > "$ROOT/neolith_boot.log" 2>&1 < /dev/null &
  disown
  sleep 4
  cd "$ROOT/server" || exit 1
  # neolith.conf listens on 4001, not the bridge's 4000 default
  setsid env MUD_PORT=4001 nohup node index.js > "$ROOT/bridge_boot.log" 2>&1 < /dev/null &
  disown
  sleep 2
  status
  echo
  echo "Open: http://127.0.0.1:8080/"
}

case "${1:-}" in
  start) start ;;
  stop) stop ;;
  status) status ;;
  *) echo "usage: $0 start|stop|status" ;;
esac
