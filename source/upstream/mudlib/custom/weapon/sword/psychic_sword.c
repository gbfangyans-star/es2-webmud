/* 靈通劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;30m靈通劍\x1b[m", ({ "psychic sword", "sword" }));
    set_weight(4800);
    init_damage(2, 15, 100, 2, "sword");
    init_damage(2, 15, 100, 2, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把以黑曜石製成的細劍, 長度跟一般短劍差不多, 非常輕巧。而劍身\n"
            "上刻滿了密密麻麻的咒文。\n");
        set("apply_weapon/sword", ([
            "magic": 5,
            "spi": 1,
            "int": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "magic": 5,
            "spi": 1,
            "int": 1,
        ]));
    }
    setup();
}
