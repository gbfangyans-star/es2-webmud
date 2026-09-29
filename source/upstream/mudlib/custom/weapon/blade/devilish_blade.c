/* 妖刀赤獄 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;34m妖刀\x1b[1;31m赤獄\x1b[0m", ({ "devilish blade of burning soul", "blade" }));
    set_weight(18800);
    init_damage(3, 21, 90, 6, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把造型妖異的魔刀﹐刀身狹長而寬﹐刀刃鋒利卻無光﹐一陣難以\n"
            "形容的光彩流動刀身﹐就仿彿是刀的血液在沸騰。\n");
        set("apply_weapon/twohanded blade", ([
            "armor_vs_fire": 20,
            "armor_vs_ice": 20,
            "armor": -20,
        ]));
    }
    setup();
}
