// /d/lee/watermelon_n1.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
田畦裡種著一排排西瓜藤，寬大的葉片鋪滿泥地。農人沿著田埂巡看瓜苗，防著路人隨手摘走尚未成熟的西瓜。
LONG
    );
    set("objects", ([
        "/d/lee/npc/farmer" : 3
    ]));
    set("exits", ([
        "west" : __DIR__"square_c",
        "east" : __DIR__"watermelon_n2",
        "south" : __DIR__"watermelon_s1"
    ]));
    setup();
}

void init()
{
    add_action("do_pick", "pick");
}

int do_pick(string arg)
{
    object melon, farmer;
    if( !arg || (arg != "西瓜" && arg != "watermelon" && arg != "melon") ) return 0;
    melon = new("/d/lee/obj/watermelon");
    if( melon->move(this_player()) ) melon->move(this_object());
    message_vision("$N彎下腰，從瓜田裡摘起一顆西瓜。\n", this_player());
    foreach(farmer in all_inventory(this_object())) {
        if( farmer->id("lee farmer") ) {
            tell_room(this_object(), farmer->name() + "怒道：誰准你亂摘田裡的西瓜！\n");
            farmer->kill_ob(this_player());
        }
    }
    return 1;
}
