/* 古岳風刃 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("古岳風刃", ({ "flurry sword", "sword" }));
    set_weight(26900);
    init_damage(4, 26, 180, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "此劍乃是劍甲門為古劍門掌門人景愈濤打造的寶劍。劍身約七指\n"
            "寬，兩臂長，金光之中似有一點藍光，幽雅而且神秘。\n");
        set("apply_weapon/twohanded sword", ([
            "intimidate": 30,
            "au-chan sword": 20,
            "defense": 20,
        ]));
    }
    setup();
}
