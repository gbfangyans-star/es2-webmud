/* 風雷刀 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("風雷刀", ({ "thunderfurry blade", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "此刀刀身細長，暗含雷光閃動，號稱摩若族第一名刀！\n");
        set("apply_weapon/blade", ([
            "armor_vs_wind": 100,
            "intimidate": 50,
            "armor_vs_lightning": 100,
            "attack": 30,
        ]));
    }
    setup();
}
