#!/bin/bash
# 幫雲端主機加上 HTTPS：安裝 Caddy 當反向代理，自動向 Let's Encrypt 申請並續約憑證。
#
# 用法（先在 Oracle 的 Security List 開放 TCP 80 和 443）：
#   bash ~/es2-webmud/deploy/oracle/https.sh               # 沒有網域：用 IP 對應的 sslip.io 網址
#   bash ~/es2-webmud/deploy/oracle/https.sh es2.example.com   # 有自己的網域（DNS 的 A 記錄要先指到主機 IP）
#
# 重複執行是安全的；換網域時再執行一次並帶上新網域即可。
set -euo pipefail

WEB_PORT="${WEB_PORT:-8080}"
IP=$(curl -fsS --max-time 5 https://ifconfig.me 2>/dev/null || true)
if [ -n "${1:-}" ]; then
    DOMAIN="$1"
elif [ -n "$IP" ]; then
    DOMAIN="$(echo "$IP" | tr . -).sslip.io"
else
    echo "查不到主機的公開 IP，請直接指定網域：bash $0 你的網域"
    exit 1
fi

echo "==== 1/3 安裝 Caddy ===="
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y caddy

echo "==== 2/3 開放主機防火牆的 80、443 port ===="
for port in 80 443; do
    if ! sudo iptables -C INPUT -p tcp --dport "$port" -m state --state NEW -j ACCEPT 2>/dev/null; then
        sudo iptables -I INPUT 1 -p tcp --dport "$port" -m state --state NEW -j ACCEPT
    fi
done
command -v netfilter-persistent >/dev/null && sudo netfilter-persistent save

echo "==== 3/3 設定 $DOMAIN → 127.0.0.1:$WEB_PORT ===="
sudo tee /etc/caddy/Caddyfile >/dev/null <<EOF
$DOMAIN {
    encode gzip
    reverse_proxy 127.0.0.1:$WEB_PORT
}
EOF
sudo systemctl enable caddy >/dev/null 2>&1 || true
sudo systemctl restart caddy

echo "等待憑證申請（最多 60 秒）..."
for _ in $(seq 1 30); do
    if curl -fsS --max-time 5 -o /dev/null "https://$DOMAIN/api/health" 2>/dev/null; then
        echo
        echo "完成！玩家網址：https://$DOMAIN/"
        echo "（原本的 http://${IP:-主機IP}:$WEB_PORT/ 仍然可以用）"
        exit 0
    fi
    sleep 2
done
echo
echo "HTTPS 還沒有回應。請確認："
echo "  1. Oracle 主控台的 Security List 已開放 TCP 80 和 443"
echo "  2. 有指定自己網域的話，DNS 已經指到 ${IP:-主機IP}"
echo "最近的記錄："
sudo journalctl -u caddy -n 20 --no-pager
exit 1
