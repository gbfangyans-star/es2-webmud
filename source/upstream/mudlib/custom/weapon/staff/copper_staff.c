/* 古銅杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("古銅杖", ({ "copper staff", "staff" }));
    set_weight(14000);
    init_damage(3, 12, 120, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一根又重又粗的銅杖，看起來沒有相當的膂力是沒有辦法使用的。\n");
    }
    setup();
}
