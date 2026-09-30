/* 指南劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m指南劍\x1b[m", ({ "daoist sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "一把十分陳舊的木劍，劍刃上還寫著不少好似經文的金字，看起來\n"
            "好像沒什麼價值。\n");
        set("apply_weapon/sword", ([
            "spi": 1,
            "taoism-storm": 15,
        ]));
    }
    setup();
}
