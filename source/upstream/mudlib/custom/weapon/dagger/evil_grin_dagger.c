/* 罪牙匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;31m罪牙匕\x1b[m", ({ "evil-grin dagger", "dagger" }));
    set_weight(8800);
    init_damage(3, 17, 85, 10, "dagger");
    init_damage(3, 17, 85, 10, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一把用上古魔獸饕餮的前牙製成的匕首﹐還殘留一股令人做嘔的臭味。\n");
        set("apply_weapon/dagger", ([
            "attack": 25,
            "force": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "attack": 25,
            "force": 5,
        ]));
    }
    setup();
}
