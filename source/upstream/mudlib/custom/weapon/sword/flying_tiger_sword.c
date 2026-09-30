/* 朱雀『白虎』劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;35m朱雀\x1b[1;37m『白虎』\x1b[1;35m劍\x1b[m", ({ "flying-tiger sword", "sword" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一把散發著異樣劍光的長劍, 劍身修長柔韌﹐劍刃鋒利而薄如蟬翼。\n"
            "劍柄處乃是虎口吞食之形﹐稍顯霸氣。\n");
        set("apply_weapon/sword", ([
            "intimidate": 10,
            "dodge": 10,
        ]));
    }
    setup();
}
