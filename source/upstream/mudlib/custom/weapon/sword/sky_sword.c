/* 昊天大劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("昊天大劍", ({ "sky sword", "sword" }));
    set_weight(17900);
    init_damage(4, 15, 86, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把難得一見的白色大劍，劍身白晰似乎蒙著一層薄霜，一股寒冷劍氣從劍身散出，手握之\n"
            "處刻有一鳳凰標誌，不知象徵著什麼。\n");
        set("apply_weapon/twohanded sword", ([
            "intimidate": 15,
            "dodge": 10,
        ]));
    }
    setup();
}
