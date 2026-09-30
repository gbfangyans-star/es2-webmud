/* 木杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("木杖", ({ "long staff", "staff" }));
    set_weight(12000);
    init_damage(3, 12, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一根用木頭削成的柺杖。\n");
    }
    setup();
}
