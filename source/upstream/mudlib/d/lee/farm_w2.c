// /d/lee/farm_w2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "農家");
    set("long", @LONG
另一戶農家的院牆由土磚砌成，門口靠著犁與鋤頭。雞鳴與人聲不時從院內傳出，顯得十分尋常。牆角堆著幾捆乾草，牆頭上還曬著幾張剛洗過的粗布，看得出這戶人家過得雖不寬裕，倒也打理得井井有條。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wroad3",
        "west" : __DIR__"farm_w1"
    ]));
    create_door("north", "柴門", "south", DOOR_CLOSED);
    setup();
    replace_program(ROOM);
}
