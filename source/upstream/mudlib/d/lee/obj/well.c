// /d/lee/obj/well.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 功能與 d/snow/npc/obj/pot.c（大水缸）相同：固定在房間裡、標記為裝水容器、
// 水量用 reset() 自動補滿，不會被用完。

inherit ITEM;

void create()
{
    object water;

    set_name("水井", ({ "well" }));
    set_max_encumbrance(180000);
    set("long", "一口普通的水井，井口以石塊砌成，井中有清水，可供村民取用。\n");
    set("no_get", 1);
    set("liquid_container", 1);
    setup();
    if( clonep() ) {
        water = new("/obj/water");
        water->set_volume(100000);
        water->move(this_object());
    }
}

varargs int accept_object(object me, object ob)
{
    if( ob )
        if( !userp(ob) )
            return 1;
    else return notify_fail("你不能將玩家放到容器裡面。\n");
}

void reset()
{
    object water;
    if( water = present("water", this_object()) )
        water->set_volume(100000);
}
