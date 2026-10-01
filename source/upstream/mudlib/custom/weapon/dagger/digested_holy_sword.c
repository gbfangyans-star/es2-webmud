/* 被腐蝕的旋芒 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("被腐蝕的旋芒", ({ "digested holy sword", "holy sword", "sword" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 55000);
        set("long",
            "昔日勇士寒於的利劍「旋芒」已經被應龍的胃液腐蝕得面目全非了 ...\n");
        set("apply_weapon/dagger", ([
            "move": 30,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "move": 30,
        ]));
    }
    setup();
}
