#!/bin/bash
# 用自己的電腦（WSL）當伺服器，透過 Cloudflare Tunnel 給玩家一個公開網址。
# 不需要 Cloudflare 帳號，也不用設定路由器；網址每次重新開啟 Tunnel 都會改變。
#
# 用法：
#   bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh start    # 確認遊戲已啟動，開 Tunnel，顯示玩家網址
#   bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh url      # 再顯示一次目前的網址
#   bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh status   # 遊戲和 Tunnel 的狀態
#   bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh stop     # 關閉 Tunnel（遊戲本身不關）
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
WEB_PORT="${WEB_PORT:-8080}"
BIN_DIR="$HOME/.local/bin"
CF="$BIN_DIR/cloudflared"
STATE_DIR="$HOME/.es2-tunnel"
LOG="$STATE_DIR/tunnel.log"
PID_FILE="$STATE_DIR/tunnel.pid"
mkdir -p "$STATE_DIR"

game_up() { curl -fsS --max-time 3 "http://127.0.0.1:$WEB_PORT/api/health" >/dev/null 2>&1; }
tunnel_pid() { [ -f "$PID_FILE" ] && kill -0 "$(cat "$PID_FILE")" 2>/dev/null && cat "$PID_FILE"; }
tunnel_url() { grep -o 'https://[a-z0-9-]*\.trycloudflare\.com' "$LOG" 2>/dev/null | tail -1; }

install_cloudflared() {
    [ -x "$CF" ] && return 0
    case "$(uname -m)" in
        x86_64) arch=amd64 ;;
        aarch64|arm64) arch=arm64 ;;
        *) echo "不支援的 CPU 架構：$(uname -m)"; exit 1 ;;
    esac
    echo "下載 cloudflared（只有第一次需要）..."
    mkdir -p "$BIN_DIR"
    curl -fsSL -o "$CF" "https://github.com/cloudflare/cloudflared/releases/latest/download/cloudflared-linux-$arch" || {
        echo "下載失敗，請確認網路後再試一次。"; rm -f "$CF"; exit 1; }
    chmod +x "$CF"
}

start_game() {
    if game_up; then echo "遊戲已在執行。"; return 0; fi
    echo "啟動遊戲..."
    if [ -x "$HOME/es2webmud_ctl.local.sh" ]; then
        "$HOME/es2webmud_ctl.local.sh" start
    else
        bash "$ROOT/es2webmud_ctl.sh" start
    fi
    for _ in $(seq 1 15); do game_up && return 0; sleep 1; done
    echo "遊戲沒有在 $WEB_PORT port 回應，請先確認遊戲能在 http://127.0.0.1:$WEB_PORT/ 打開。"
    exit 1
}

case "${1:-start}" in
start)
    install_cloudflared
    start_game
    if pid=$(tunnel_pid); then
        echo "Tunnel 已在執行（pid $pid）。"
    else
        : > "$LOG"
        setsid nohup "$CF" tunnel --no-autoupdate --url "http://127.0.0.1:$WEB_PORT" > "$LOG" 2>&1 < /dev/null &
        echo $! > "$PID_FILE"
        echo "開啟 Tunnel 中，請稍候..."
        for _ in $(seq 1 30); do [ -n "$(tunnel_url)" ] && break; sleep 1; done
    fi
    url=$(tunnel_url)
    if [ -n "$url" ]; then
        echo
        echo "玩家網址：$url"
        echo "（電腦和 WSL 要保持開著；重新開 Tunnel 後網址會改變）"
    else
        echo "沒有拿到網址，最後幾行記錄："
        tail -n 15 "$LOG"
        exit 1
    fi
    ;;
url)
    if tunnel_pid >/dev/null && [ -n "$(tunnel_url)" ]; then tunnel_url; else echo "Tunnel 沒有在執行。"; fi
    ;;
status)
    game_up && echo "遊戲：執行中（port $WEB_PORT）" || echo "遊戲：沒有回應"
    if pid=$(tunnel_pid); then echo "Tunnel：執行中（pid $pid） $(tunnel_url)"; else echo "Tunnel：已關閉"; fi
    ;;
stop)
    if pid=$(tunnel_pid); then kill "$pid"; rm -f "$PID_FILE"; echo "Tunnel 已關閉（遊戲仍在執行）。"; else echo "Tunnel 沒有在執行。"; fi
    ;;
*)
    echo "用法：$0 start|url|status|stop"; exit 1 ;;
esac
