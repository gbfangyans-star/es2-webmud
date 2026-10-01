/* 無情匕 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("無情匕", ({ "coldblood dagger", "dagger" }));
    set_weight(8800);
    init_damage(3, 17, 85, 10, "dagger");

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 75000);
        set("long",
            "一把用寒鐵打製的殺人利器，普通人看到就會發抖了。\n");
        set("apply_weapon/dagger", ([
            "backstab": 10,
            "intimidate": 40,
            "dagger": 10,
        ]));
    }
    setup();
}
