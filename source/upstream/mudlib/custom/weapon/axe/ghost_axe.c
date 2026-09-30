/* 萬夫巨斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("萬夫巨斧", ({ "ghost axe", "axe" }));
    set_weight(20000);
    init_damage(4, 18, 135, 3, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 300);
        set("long",
            "一柄巨大異常的雪銀色大斧, 傳說中太蠻馱鬼將的武器。\n");
    }
    setup();
}
