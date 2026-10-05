/*---
description: 天朝公告，放在雪亭鎮飲風客棧大堂。只有見習巫師（apprentice）以上可以張貼，玩家只能閱讀。
---*/
inherit BULLETIN_BOARD;

private void
create()
{
  set_name("天朝公告", ({ "celestial empire board", "board" }));
  set("location", "/d/snow/inn_hall");
  set("board_id", "celestial");
  set("capacity", 50);
  set("post_wiz_level", 2);   // (apprentice) 以上
  setup();
  set("long", "這是天朝的公告欄，刊登巫師發布的各項公告與消息，玩家可以閱讀，但不能張貼。\n");
}

// 名稱後面顯示「Celestial  Empire Board」（預設只會把第一個字母大寫）。
string query_id() { return "Celestial  Empire Board"; }
