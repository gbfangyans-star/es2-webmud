/* 青龍白虎斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;34m青龍\x1b[1;37m白虎斧\x1b[m", ({ "dragon-tiger axe", "axe" }));
    set_weight(5000);
    init_damage(3, 8, 60, 9, "axe");
    init_damage(3, 4, 60, 9, "secondhand axe");

    if( !clonep() ) {
        set("wield_as", ({ "axe", "secondhand axe" }));
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一柄相當巨大的大斧﹐不斷的發出嗡嗡的聲響﹐好像對血的飢渴。\n");
        set("apply_weapon/secondhand axe", ([
            "cor": 1,
            "str": 1,
        ]));
    }
    setup();
}
