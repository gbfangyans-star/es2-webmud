#include <ansi.h>
inherit ROOM;
void create(){ set("short","老松寨"); set("long",@LONG
这里应该是老松寨了，木墙险要处堆着沙包石堆，显然埋伏着人手。大寨的门在西边，东边越过一排木桩就是大厅。
LONG
); set("exits",(["west":__DIR__"keep1","east":__DIR__"keep3"])); set("objects",([__DIR__"../npc/bandit_guard":2,__DIR__"../npc/bandit_leader":1])); set("map/area","老松林"); set("map/layer","老松寨"); setup(); }
int valid_leave(object me,string exit){ int i; object ob; if(exit!="east" || !query("exits/west")) return 1; message("vision",HIY "你听到身后有人大叫把门关上，接着轰地一声，通往外面的大门已被大石堵死。\n" NOR,this_object()); delete("exits/west"); if(ob=find_object(__DIR__"keep1")) ob->delete("exits/east"); i=5; while(i--){ ob=new(__DIR__"../npc/bandit_guard"); ob->move(this_object()); ob->kill_ob(me); } return 1; }
void reset(){ object ob; ::reset(); set("exits/west",__DIR__"keep1"); if(ob=find_object(__DIR__"keep1")) ob->set("exits/east",__FILE__); }
void pipe_notify(){ object ob; message("vision","你听到一阵轧轧的轮盘绞动声，堵住门口的大石慢慢地被移开了。\n",this_object()); set("exits/west",__DIR__"keep1"); if(ob=find_object(__DIR__"keep1")) ob->set("exits/east",__FILE__); }
