/* 神農打穀鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("神農打穀鞭", ({ "whip of alchemy cereal", "whip" }));
    set_weight(4800);
    init_damage(3, 9, 65, 5, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一條用植物編織成的軟鞭，這條鞭子是先將植物莖梗浸泡在特別的藥水\n"
            "中四十九天，之後再經日曬四十九天，最後再編織在一起。\n");
        set("apply_weapon/whip", ([
            "armor": 10,
            "alchemy-medication": 20,
        ]));
    }
    setup();
}
