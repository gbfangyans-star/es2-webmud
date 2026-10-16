// /d/qiaoyin/tree_tomb.c — 喬陰縣（L10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹王墳");
    set("long", @LONG
這裡便是喬陰縣著名的樹王墳了﹐一株約十多人合抱的大樹齊腰而斷﹐上面的紋理因為經常被撫摸而清晰可見﹐樹王墳的周圍方圓數十丈內都沒有建築﹐顯然縣城的居民對樹王墳十分崇敬﹐樹旁立著一塊石碑﹐上面刻得有字。
LONG
    );
    set("detail", ([
        "石碑" : "一塊青石碑，碑上的字跡已經有些風化，仔細辨認，刻的是：「樹王墳記：此樹植於喬陰立縣之初，枝葉蔽日，蔭庇一方，鄉人奉為樹王。某歲夏夜大雷，樹身齊腰而斷，而根猶生。鄉人以為樹王代全城受劫，遂立此碑以誌其德，歲時祭之。後之來者，撫樹而思，毋忘其恩。」\n",
    ]));
    set("exits", ([
        "west" : __DIR__"west_street4",
        "east" : __DIR__"east_street1",
        "north" : __DIR__"north_street3",
        "south" : __DIR__"south_street1",
    ]));
    set("objects", ([
        __DIR__"npc/fortune_teller" : 1,
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
