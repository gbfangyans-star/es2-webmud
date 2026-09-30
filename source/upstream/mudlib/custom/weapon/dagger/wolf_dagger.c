/* 狼匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("狼匕", ({ "wolf dagger", "dagger" }));
    set_weight(4400);
    init_damage(3, 8, 50, 5, "dagger");
    init_damage(3, 8, 50, 5, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 3500);
        set("long",
            "狼匕, 又俗稱郎匕, 為待嫁閨女出門時常帶之防身武器, 據聞可以帶來好運,\n"
            "『豺狼不近身, 兒郎不離身』.你手上這把刃身泛黃, 隱現寒氣, 並有\"女兒村\"\n"
            "之標記。\n");
        set("apply_weapon/dagger", ([
            "backstab": 5,
            "sneak": 5,
            "attack": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "backstab": 5,
            "sneak": 5,
            "attack": 5,
        ]));
    }
    setup();
}
