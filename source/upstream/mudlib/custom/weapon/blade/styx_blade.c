/* 幽冥刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("幽冥刀", ({ "styx blade", "blade" }));
    set_weight(4000);
    init_damage(2, 13, 80, 0, "blade");
    init_damage(2, 6, 80, 0, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "secondhand blade", "blade" }));
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把暗黑色的短刀，刀柄的部分還寫著一個「風」字，這把刀拿在手上\n"
            "不時還傳出陣陣的幽冥之氣。\n");
        set("apply_weapon/secondhand blade", ([
            "parry": 10,
            "secondhand blade": 15,
        ]));
    }
    setup();
}
