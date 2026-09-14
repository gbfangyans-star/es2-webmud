inherit ITEM;
void create(){ set_name("竹管",({"bamboo pipe","pipe"})); set_weight(100); set("unit","根"); set("long","一根不起眼的竹管。\n"); set("value",10); }
void init(){ add_action("do_play","play"); add_action("do_play","blow"); }
int do_play(string arg){ if(!arg || !id(arg)) return notify_fail("你要吹什么？\n"); message_vision("$N拿起竹管吹了几声。\n",this_player()); if(environment(this_player())) environment(this_player())->pipe_notify(); return 1; }
