/* 「魈」 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("「魈」", ({ "xiao dagger", "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "secondhand dagger");
    init_damage(2, 15, 100, 8, "dagger");

    if( !clonep() ) {
        set("wield_as", ({ "secondhand dagger", "dagger" }));
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把赤紅色的匕首，上頭有著像鬼一般的圖案，當你看著這把匕首時，心中感覺\n"
            "異常的平靜。\n");
        set("apply_weapon/secondhand dagger", ([
            "parry": 10,
            "dodge": 10,
        ]));
        set("apply_weapon/dagger", ([
            "parry": 10,
            "dodge": 10,
        ]));
    }
    setup();
}
