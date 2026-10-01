/* 天命刃 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("天命刃", ({ "dagger of fate", "dagger" }));
    set_weight(6300);
    init_damage(3, 12, 75, 7, "dagger");

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "據說這是天靈「穹氤」所用的武器，不過看起來好像沒有甚麼殺傷力 ...\n");
        set("apply_weapon/dagger", ([
            "cps": 5,
            "spi": 1,
            "int": 1,
            "wis": 2,
        ]));
    }
    setup();
}
