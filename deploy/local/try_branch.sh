#!/bin/bash
# 家裡電腦（WSL）切換要測試的版本，並重開本機遊戲（http://127.0.0.1:8080/）。
#
# 用法：
#   測試還沒合併的新內容（開發分支）：
#     curl -fsSL https://raw.githubusercontent.com/gbfangyans-star/es2-webmud/claude/epic-ramanujan-wuyis3/deploy/local/try_branch.sh | bash
#   切回正式版（main）：
#     curl -fsSL https://raw.githubusercontent.com/gbfangyans-star/es2-webmud/claude/epic-ramanujan-wuyis3/deploy/local/try_branch.sh | bash -s main
#
# 玩家存檔（data/user、data/login）不受影響。
set -u

ROOT="${ES2_DIR:-$HOME/es2-webmud}"
TARGET="${1:-dev}"
if [ "$TARGET" = "main" ]; then
    REPO=https://github.com/wolfer168/es2-webmud.git; BRANCH=main; LOCAL=main
else
    REPO=https://github.com/gbfangyans-star/es2-webmud.git; BRANCH=claude/epic-ramanujan-wuyis3; LOCAL=es2-test
fi
cd "$ROOT" || { echo "找不到 $ROOT"; exit 1; }

echo "==== 1/3 下載 $BRANCH ===="
OLD=$(git rev-parse HEAD)
git fetch "$REPO" "$BRANCH" || { echo "下載失敗，請確認網路。"; exit 1; }
if ! git checkout -B "$LOCAL" FETCH_HEAD; then
    echo
    echo "切換失敗：有被遊戲改過的檔案擋住。把上面列出的檔案貼給 Claude，或執行"
    echo "  git -C $ROOT stash   之後再跑一次。"
    exit 1
fi
NEW=$(git rev-parse HEAD)

echo "==== 2/3 Neolith 原始碼有變動才重新編譯 ===="
if [ "$OLD" != "$NEW" ] && git diff --name-only "$OLD" "$NEW" | grep -q '^source/upstream/neolith/'; then
    (cd source/upstream/neolith && cmake --preset linux && cmake --build --preset pr-linux --target neolith) || exit 1
else
    echo "沒有變動，略過。"
fi
if [ "$OLD" != "$NEW" ] && git diff --name-only "$OLD" "$NEW" | grep -q '^server/package'; then
    (cd server && npm ci --omit=dev)
fi

echo "==== 3/3 清除編譯快取並重開本機遊戲 ===="
rm -rf source/upstream/mudlib/bin/*
if [ -x "$HOME/es2webmud_ctl.local.sh" ]; then
    "$HOME/es2webmud_ctl.local.sh" start
else
    bash "$ROOT/es2webmud_ctl.sh" start
fi
echo
echo "目前版本：$(git log --oneline -1)（$LOCAL）"
echo "請打開 http://127.0.0.1:8080/ 測試。"
