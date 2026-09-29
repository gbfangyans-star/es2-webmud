/* 邪兵『火麟』 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("邪兵\x1b[1;31m『火麟』\x1b[0m", ({ "grin weapon", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");
    init_damage(3, 6, 90, 5, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "blade", "secondhand blade" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把通身火紅的詭異兵器，似劍又似刀，柄處還有個奇異的孔穴。\n");
        set("apply_weapon/secondhand blade", ([
            "damage": 5,
            "cor": 1,
        ]));
    }
    setup();
}
