inherit ROOM;
void create(){ set("short","老松寨秘密入口"); set("long",@LONG
这里只见一个木头搭成的大门，门框上挂着几具不知名动物的头骨和一些铁链，外面铺着干枯松枝，在森林里很不容易发觉。
LONG
); set("exits",(["west":__DIR__"pine2","east":__DIR__"keep2"])); set("objects",([__DIR__"../npc/bandit_guard":4])); set("map/area","老松林"); set("map/layer","老松寨"); setup(); }
