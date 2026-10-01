/* 赤魈心 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("赤魈心", ({ "chixiao necklace", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 14000);
        set("long",
            "赤魈心為十三精靈之一的山鬼「赤魈」所有。數十年前，大邪道\n"
            "人曾偶得此物。而後有贈予只有一面之緣，又沒入師門的徒弟龍\n"
            "天威。自龍天威因受江湖追殺而銷聲匿跡之後，此物便從世上消\n"
            "失了。不過有好事者稱，曾見過龍天威的姪女龍卿佩戴此物。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
