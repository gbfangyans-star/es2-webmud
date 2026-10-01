/* 裁決之杖 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("裁決之杖", ({ "staff of judgement", "staff" }));
    set_weight(19000);
    init_damage(3, 20, 202, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "根");
        set("value", 45000);
        set("long",
            "一根用黃銅打製的重杖，杖首為一展翅大鵬，杖身則有巨蟒纏繞。華麗中流露\n"
            "出一股不可侵犯的威嚴。\n");
        set("apply_weapon/twohanded staff", ([
            "armor": 25,
            "parry": 10,
            "defense": 30,
            "armor_vs_lightning": 150,
        ]));
    }
    setup();
}
