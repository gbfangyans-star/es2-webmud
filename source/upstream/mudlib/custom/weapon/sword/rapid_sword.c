/* 疾風劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("疾風劍", ({ "rapid sword", "sword" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "sword");
    init_damage(3, 16, 120, 6, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一把細長的軟劍，劍刃就不斷抖動迎風做響。\n");
        set("apply_weapon/sword", ([
            "wind_damage": 25,
            "intimidate": 50,
            "cor": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "wind_damage": 25,
            "intimidate": 50,
            "cor": 1,
        ]));
    }
    setup();
}
