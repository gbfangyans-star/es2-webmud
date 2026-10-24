#!/bin/bash
# 雲端主機更新到最新版本：備份玩家資料 → 拉最新程式 → 需要時重新編譯 → 清快取 → 重開。
# 用法：bash ~/es2-webmud/deploy/oracle/update.sh
set -euo pipefail

BRANCH="${BRANCH:-main}"
APP_DIR="${APP_DIR:-$HOME/es2-webmud}"
MUD="$APP_DIR/source/upstream/mudlib"
BACKUP_DIR="${BACKUP_DIR:-$HOME/es2-backups}"

echo "==== 1/4 備份玩家資料到 $BACKUP_DIR ===="
mkdir -p "$BACKUP_DIR"
STAMP=$(date +%Y%m%d-%H%M%S)
tar -czf "$BACKUP_DIR/data-$STAMP.tar.gz" -C "$MUD" data
ls -1t "$BACKUP_DIR"/data-*.tar.gz | tail -n +15 | xargs -r rm -f   # 只留最近 14 份
echo "已備份：data-$STAMP.tar.gz"

echo "==== 2/4 拉最新程式（分支 $BRANCH）===="
OLD=$(git -C "$APP_DIR" rev-parse HEAD)
git -C "$APP_DIR" fetch origin "$BRANCH"
git -C "$APP_DIR" checkout -B "$BRANCH" "origin/$BRANCH"
NEW=$(git -C "$APP_DIR" rev-parse HEAD)

echo "==== 3/4 Neolith 原始碼有變動才重新編譯 ===="
if [ "$OLD" != "$NEW" ] && git -C "$APP_DIR" diff --name-only "$OLD" "$NEW" | grep -q '^source/upstream/neolith/'; then
    # 記憶體不足 2GB 時一次只編譯一個檔案，避免記憶體用光而中斷。
    MEM_MB=$(awk '/MemTotal/ {print int($2/1024)}' /proc/meminfo)
    [ "$MEM_MB" -lt 2000 ] && export CMAKE_BUILD_PARALLEL_LEVEL="${CMAKE_BUILD_PARALLEL_LEVEL:-1}"
    cd "$APP_DIR/source/upstream/neolith"
    cmake --preset linux
    cmake --build --preset pr-linux --target neolith
else
    echo "沒有變動，略過。"
fi
if git -C "$APP_DIR" diff --name-only "$OLD" "$NEW" | grep -q '^server/package'; then
    (cd "$APP_DIR/server" && npm ci --omit=dev)
fi

# 玩家版天朝圖鑑（web/codex.html）依目前的遊戲內容重新產生；失敗也不影響更新。
python3 "$APP_DIR/tools/build_player_codex.py" || echo "（圖鑑產生失敗，沿用舊的圖鑑）"
mkdir -p "$MUD/log/static"   # 自殺、複製物品等事件紀錄要寫在這裡（舊主機可能沒有這個資料夾）
# 自動安全更新（unattended-upgrades）裝完後，needrestart 會把用到更新程式庫的服務重開；
# 遊戲與網頁橋接程式不要自動重開（會讓線上玩家斷線），由管理者自己選時間重開。
if [ -d /etc/needrestart/conf.d ]; then
    sudo tee /etc/needrestart/conf.d/es2-webmud.conf >/dev/null <<'NREOF'
# 自動更新後不要自動重開遊戲與網頁橋接程式，由管理者自己選時間重開
$nrconf{override_rc}{qr(^es2-mud\.service$)} = 0;
$nrconf{override_rc}{qr(^es2-web\.service$)} = 0;
NREOF
fi
echo "==== 4/4 清除編譯快取並重開 ===="
rm -rf "$MUD/bin/"*
sudo systemctl restart es2-mud
sleep 4
sudo systemctl restart es2-web
sleep 2
systemctl is-active es2-mud es2-web
echo "已更新到 $(git -C "$APP_DIR" log --oneline -1)"
