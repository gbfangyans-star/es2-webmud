/* 雨神之牙 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

// 原資料註：開光後，需要膂力 35（重量 36000）、限哭笑門（門派尚未製作，之後補上）。
// 特殊能力 invoke 依使用者指示不製作。

void create()
{
    set_name("\x1b[1;36m雨神之牙\x1b[m", ({ "rainlord's tooth", "staff" }));
    set_weight(36000);
    init_damage(4, 18, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 75000);
        set("long",
            "這是一根一人來高的龍牙，龍牙上面似乎附著一層薄冰，映射出\n"
            "藍色的寒光。(特殊能力: invoke)\n");
        set("apply_weapon/twohanded staff", ([
            "wis": 4,
            "taoism-freeze": 30,
            "armor": 50,
            "armor_vs_ice": 100,
        ]));
    }
    setup();
}
