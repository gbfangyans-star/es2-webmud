from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
MUD = ROOT / "source/upstream/mudlib"
npc = (MUD/"custom/snow/npc/zhenghe_zhongzai.c").read_text()
room = (MUD/"d/snow/square_w.c").read_text()
char = (MUD/"std/char.c").read_text()
checks = {
    "spawn_at_rainbow_stone": '"/custom/snow/npc/zhenghe_zhongzai" : 1' in room and '__DIR__"obj/stone" : 1' in room,
    "colored_name": 'HIY "正禾老變態"' in npc and 'HIC "［中仔］"' in npc,
    "rps_command": 'add_action("do_rps", "猜拳")' in npc,
    "three_hands": all(x in npc for x in ["剪刀", "石頭", "布"]),
    "reward_50_coin": 'money->set_amount(50)' in npc,
    "lose_10_percent": all(x in npc for x in ['query_stat("gin") / 10', 'query_stat("kee") / 10', 'query_stat("sen") / 10']),
    "pinch_text": "伸手往你胸口狠狠捏了一把" in npc,
    "unconscious_30_seconds": 'call_out("revive", 30);' in char,
}
for k,v in checks.items():
    print(("PASS" if v else "FAIL"), k)
raise SystemExit(0 if all(checks.values()) else 1)
