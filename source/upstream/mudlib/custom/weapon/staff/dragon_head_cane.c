/* 龍頭柺 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("龍頭柺", ({ "dragon-head cane", "staff" }));
    set_weight(13200);
    init_damage(2, 16, 120, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一根青銅杖﹐杖頭乃是一顆精彫細刻的老龍頭﹐龍身纏繞著\n"
            "著杖身﹐整根杖與龍渾然一體。\n");
        set("apply_weapon/twohanded staff", ([
            "damage": 10,
            "attack": 20,
        ]));
    }
    setup();
}
