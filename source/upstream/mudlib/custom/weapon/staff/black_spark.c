/* 離玄光熾 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("離玄光熾", ({ "black spark", "staff" }));
    set_weight(21400);
    init_damage(3, 24, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一把材料不明的純白重杖，發著柔和的微光。\n");
        set("apply_weapon/twohanded staff", ([
            "str": 2,
            "damage": 20,
            "wittiness": 30,
        ]));
    }
    setup();
}
