# 用自己的電腦上線（Cloudflare Tunnel）

遊戲照常在自己電腦的 WSL 裡跑，Cloudflare Tunnel 給一個公開的 https 網址，玩家用瀏覽器打開就能玩。
不需要 Cloudflare 帳號、不用綁信用卡、不用設定路由器。

## 開啟

```bash
bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh start
```

- 第一次會自動下載 `cloudflared` 到 `~/.local/bin/`。
- 遊戲沒在跑會先幫你啟動（用 `~/es2webmud_ctl.local.sh start`）。
- 最後顯示「玩家網址：https://xxxx.trycloudflare.com」，把這個網址給玩家。

## 其他指令

| 用途 | 指令 |
|---|---|
| 再看一次網址 | `bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh url` |
| 看狀態 | `bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh status` |
| 關閉 Tunnel（遊戲不關） | `bash ~/es2-webmud/deploy/tunnel/es2_tunnel.sh stop` |

## 注意

- 電腦和 WSL 要一直開著，關機或休眠玩家就會斷線。Windows 的「睡眠」建議設成「永不」。
- 每次重新開 Tunnel，網址都會改變。想要固定網址，需要免費的 Cloudflare 帳號加上自己的網域，之後可以再設定。
- 更新遊戲（`~/es2_update.sh`）時 Tunnel 不用關，網址也不會變；遊戲重開期間玩家會短暫斷線。
- 這種免帳號的 Tunnel 是 Cloudflare 提供試用的，沒有穩定性保證，適合先給朋友測試。要長期開放建議改用雲端主機（見 `docs/DEPLOY_ORACLE.md`，腳本也適用於其他 Ubuntu 24.04 的 VPS）。
