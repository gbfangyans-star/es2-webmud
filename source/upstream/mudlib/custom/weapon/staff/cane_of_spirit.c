/* 聖靈禪杖 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("聖靈禪杖", ({ "cane of spirit", "cane" }));
    set_weight(19000);
    init_damage(3, 20, 202, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "根");
        set("value", 45000);
        set("long",
            "一根天藍色的禪杖，看起來晶瑩剔透，可是拿在手裡卻是異常沉重。\n");
        set("apply_weapon/twohanded staff", ([
            "armor_vs_wind": 50,
            "armor_vs_fire": 70,
            "armor_vs_ice": 40,
            "armor_vs_lightning": 100,
        ]));
    }
    setup();
}
