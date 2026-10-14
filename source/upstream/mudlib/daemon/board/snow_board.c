/*---
description: 雪亭鎮留言板，放在雪亭鎮廣場西邊，所有玩家都可以閱讀與張貼。
---*/
inherit BULLETIN_BOARD;

private void
create()
{
  set_name("雪亭鎮留言板", ({ "snow town board", "board" }));
  set("location", "/d/snow/square_w");
  set("board_id", "snow");
  set("capacity", 100);
  setup();
  set("long", "這是雪亭鎮廣場上的留言板，來往的旅人常在這裡留下消息，誰都可以看，也都可以寫。\n");
}

// 名稱後面顯示「Snow Town Board」（預設只會把第一個字母大寫）。
string query_id() { return "Snow Town Board"; }
