/* 雨神之牙 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("\x1b[1;36m雨神之牙\x1b[m", ({ "rainlord's tooth", "staff" }));
    set_weight(21400);
    init_damage(4, 18, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "這是一根一人來高的龍牙，龍牙上面似乎附著一層薄冰，映射出\n"
            "藍色的寒光。\n");
        set("apply_weapon/twohanded staff", ([
            "armor": 50,
            "wis": 6,
            "parry": 10,
            "armor_vs_ice": 100,
            "taoism-freeze": 30,
            "taoism-cloud": 20,
        ]));
    }
    setup();
}
