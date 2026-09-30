/* 嗜血巨斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;31m嗜血巨斧\x1b[m", ({ "blood axe", "axe" }));
    set_weight(16500);
    init_damage(3, 16, 133, 10, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 40000);
        set("long",
            "一把有兩面斧刃的深紅色大斧，似乎不是凡間的兵器，握柄處刻有一鳳凰標誌。\n");
        set("apply_weapon/twohanded axe", ([
            "damage": 10,
            "powerblow": 15,
            "heavy_parry": 10,
        ]));
    }
    setup();
}
