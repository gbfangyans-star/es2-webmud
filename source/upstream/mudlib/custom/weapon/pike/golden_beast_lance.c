/* 金龍豹紋槍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("金龍豹紋槍", ({ "golden beast lance", "pike" }));
    set_weight(23000);
    init_damage(4, 20, 150, 10, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一把異常沉重的黃銅大矛，長矛之上的道道黑色暗紋想必就是其名字的由來。\n");
        set("apply_weapon/twohanded pike", ([
            "attack": 50,
            "str": 5,
            "armor": 50,
        ]));
    }
    setup();
}
