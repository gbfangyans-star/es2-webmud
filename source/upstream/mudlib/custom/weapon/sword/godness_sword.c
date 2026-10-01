/* 西山仙劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("西山仙劍", ({ "godness sword", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "西山玄女族人與天朝結盟時贈送天朝的寶劍。\n");
        set("apply_weapon/sword", ([
            "spell": 20,
            "attack": 30,
            "wittiness": 30,
        ]));
    }
    setup();
}
