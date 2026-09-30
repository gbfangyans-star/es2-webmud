/* 地煞斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;37m地煞斧\x1b[m", ({ "hell twibil", "axe" }));
    set_weight(20000);
    init_damage(4, 18, 120, 3, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一把異常巨大的雙刃斧﹐斧柄上刻的字已經十分模糊了﹐據說﹐此斧來自形\n"
            "天的古老部落﹐黃泉村。\n");
        set("apply_weapon/twohanded axe", ([
            "heavy_parry": 10,
            "int": -2,
            "str": 2,
        ]));
    }
    setup();
}
