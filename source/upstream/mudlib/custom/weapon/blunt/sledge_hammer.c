/* 大金槌 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("大金槌", ({ "sledge hammer", "blunt" }));
    set_weight(10800);
    init_damage(5, 6, 240, 0, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "一把沈重的黃銅大槌，只有膂力雄強的人才使得動的兵器。\n");
    }
    setup();
}
