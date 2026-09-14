inherit ROOM;
void create(){ set("short","老松寨大厅"); set("long",@LONG
这里就是老松寨的大厅。北边地面铺着巨大熊皮，四周散落着取暖火盆和上锁木箱；中央有个大坑，许多头骨浸在发着恶臭的黄水中。
LONG
); set("exits",(["west":__DIR__"keep2"])); set("objects",([__DIR__"../npc/bandit_leader":3,__DIR__"../npc/bandit_commander":1])); set("map/area","老松林"); set("map/layer","老松寨"); setup(); }
