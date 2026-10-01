/* 蓮花禪杖 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("蓮花禪杖", ({ "flower cane", "staff" }));
    set_weight(21400);
    init_damage(3, 24, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "根");
        set("value", 95000);
        set("long",
            "一把御賜白象寺的黃銅杖，杖頂端雕有如來座下蓮花一朵。\n");
        set("apply_weapon/twohanded staff", ([
            "cps": 3,
            "armor": 15,
            "attack": 30,
        ]));
    }
    setup();
}
