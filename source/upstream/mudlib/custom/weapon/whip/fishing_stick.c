/* 生鐵釣竿 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("生鐵釣竿", ({ "fishing stick", "whip" }));
    set_weight(6300);
    init_damage(3, 12, 100, 7, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 7500);
        set("long",
            "一支用生鐵打造的釣杆，不僅可以用來釣魚，也是把不錯的防身武器。\n");
        set("apply_weapon/whip", ([
            "halieutics": 5,
            "str": 1,
        ]));
    }
    setup();
}
