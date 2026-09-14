inherit ROOM; void create(){ set("short","瀑布前"); set("long",@LONG
你现在正站在瀑布前的一个小水潭里，水潭大约深可及胸，淹不死
人，一条白练般的瀑布(waterfall)从数百丈高的悬崖上冲激而下，溅
得你全身湿透，水潭三面都被高耸的山壁(cliff)所包围，只有南面沿
著一条山涧可以出去。
LONG
); set("detail",(["waterfall":"白练般的瀑布从数百丈高处冲激而下，水声震耳，飞散的水雾把四周岩石都打得湿滑。\n","cliff":"三面的山壁高耸陡直，岩面被水气浸得湿滑，几乎找不到容易落脚的地方。\n"])); set("exits",(["south":__DIR__"riverbank2"])); set("resource/water",1); set("map/area","老松林"); set("map/layer","谷底"); setup(); }
