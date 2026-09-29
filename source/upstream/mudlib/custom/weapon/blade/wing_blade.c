/* 蟬翼刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;37m蟬翼刀\x1b[m", ({ "wing blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一把絕世好刀, 形似蟬翼, 刀身薄且鋒利, 非名匠無法鑄出此刀。\n");
        set("apply_weapon/blade", ([
            "attack": 25,
            "dex": 2,
        ]));
    }
    setup();
}
