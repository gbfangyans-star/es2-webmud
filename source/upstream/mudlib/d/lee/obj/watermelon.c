// /d/lee/obj/watermelon.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 一顆西瓜可以 eat 四次；前三次與最後一次的敘述不同，吃完後西瓜消失。

inherit COMBINED_ITEM;
inherit F_FOOD;

#define BITES_PER_MELON 4

void create()
{
    set_name("西瓜", ({ "watermelon", "melon" }));
    if( !clonep() ) {
        set("unit", "堆");
        set("base_unit", "顆");
        set("base_value", 50);
        set("base_weight", 1200);
        set("long", "一顆沉甸甸的西瓜，外皮翠綠。\n");
    }
    set_amount(1);
    set("bites_left", BITES_PER_MELON);
    setup();
}

// Overrides F_FOOD::stuff_ob() — the generic single-value food model doesn't
// support per-bite messages or restoring 飲水(water), so this melon handles
// its own "eat" logic instead of using food_stuff.
int stuff_ob(object me)
{
    int bites;

    bites = query("bites_left") - 1;

    me->supplement_stat("food", 20);
    me->supplement_stat("water", 50);

    if( bites > 0 ) {
        set("bites_left", bites);
        message_vision("$N稀哩呼嚕的吃了幾口西瓜。\n", me);
        return 1;
    }

    message_vision("$N狼吞虎嚥地把西瓜吃光了。\n", me);
    if( (int)this_object()->query_amount() > 1 ) {
        add_amount(-1);
        set("bites_left", BITES_PER_MELON);
    } else
        destruct(this_object());
    return 1;
}
