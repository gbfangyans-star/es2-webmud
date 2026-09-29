/* 紫薇伏龍刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;35m紫薇伏龍刀\x1b[m", ({ "purple dragon blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");
    init_damage(3, 6, 90, 5, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "secondhand blade", "blade" }));
        set("unit", "把");
        set("value", 4000);
        set("long",
            "一柄散發著陣陣紫氣的短刀。鑄造此刀的材料和工藝來源於奐族，所以\n"
            "天朝境內很少有人用過這把短刀。\n");
        set("apply_weapon/secondhand blade", ([
            "damage": 5,
            "str": 1,
        ]));
        set("apply_weapon/blade", ([
            "damage": 5,
            "str": 1,
        ]));
    }
    setup();
}
