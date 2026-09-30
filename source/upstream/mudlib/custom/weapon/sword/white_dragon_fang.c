/* 白龍牙 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m白龍牙\x1b[m", ({ "dragon sword", "sword" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "一把雪白的長劍，劍身猶如骨質般發出幽暗的光澤，劍鋒處有一數道細小\n"
            "的裂紋斷斷續續的延伸到叉開的劍尖處...\n");
        set("apply_weapon/sword", ([
            "force": 10,
            "damage": 10,
            "sword": 10,
        ]));
    }
    setup();
}
