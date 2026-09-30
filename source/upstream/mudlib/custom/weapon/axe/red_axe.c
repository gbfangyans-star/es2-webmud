/* 深朱闊斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("深朱闊斧", ({ "red axe", "axe" }));
    set_weight(15500);
    init_damage(4, 12, 100, 5, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一柄血紅色的大斧, 斧柄上烙著「青邪」兩字\n");
        set("apply_weapon/twohanded axe", ([
            "parry": 15,
            "attack": 10,
        ]));
    }
    setup();
}
