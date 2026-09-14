ES2 zMUD 4.62 Big5 Bridge PATCH v1

Purpose
- Keep ES2 / Neolith / WebMUD in UTF-8.
- Let old zMUD 4.62 connect using Big5/CP950 without Chinese mojibake.
- Preserve Telnet IAC negotiation bytes instead of transcoding them.

Files (all new; no existing project file is overwritten)
- zmud_big5_bridge.ps1
- START_ZMUD_BRIDGE.bat
- START_ES2_INTERNET_ZMUD.bat

Install
Copy these files to the ES2 project root, beside START_ES2_INTERNET.bat.

Use
1. Double-click START_ES2_INTERNET_ZMUD.bat.
2. Local zMUD 4.62: Host 127.0.0.1, Port 4002.
3. Remote zMUD 4.62: Host = server public IP/domain, Port 4002.
4. Router: forward TCP 4002 to the ES2 server PC.
5. Windows Firewall: allow inbound TCP 4002.

Ports
- 4000: WebMUD public
- 4001: Neolith UTF-8 internal (recommended not public)
- 4002: zMUD Big5 public

Notes
- Big5 cannot represent every Unicode symbol. Unsupported characters are replaced with '?'.
- Traditional Chinese ES2 text covered by CP950 should display normally.
- This patch does not modify mudlib, Web UI, player data, Wizard permissions, or existing startup files.
