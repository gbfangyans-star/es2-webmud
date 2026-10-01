/* 古鄔匕 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("古鄔匕", ({ "ancient dagger", "dagger" }));
    set_weight(8800);
    init_damage(3, 17, 85, 10, "dagger");

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "這是一把北方大漠的古鄔赤族納貢給天朝帝國的神秘匕首。\n");
        set("apply_weapon/dagger", ([
            "intimidate": 50,
            "attack": 30,
            "stealing": 30,
        ]));
    }
    setup();
}
