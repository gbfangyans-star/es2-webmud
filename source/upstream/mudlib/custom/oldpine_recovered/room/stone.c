/* venomsnake spawn held until recovered NPC set is staged. */
inherit ROOM; void create(){ set("short","大青石上"); set("long",@LONG
你现在正站在一块突出的大青石上，虽然有点滑，你还是能站稳，
往四周看，除了长满青苔的石壁似乎无路可走，不过大青石边缘仍有落脚之处，看起来可以试著向下攀爬(climb down)。
LONG
); set("map/area","老松林"); set("map/layer","洞穴"); setup(); }
void init(){ add_action("do_climb","climb"); } int do_climb(string arg){ if(!arg||arg!="down") return notify_fail("想爬下去(down)吗？\n"); message_vision("$N迅速地爬下大青石。\n",this_player()); this_player()->move(__DIR__"cave1"); return 1; }
