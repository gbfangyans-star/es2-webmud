/* 雷神之怒 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("\x1b[1;33m雷神之怒\x1b[m", ({ "thunder god's anger", "blunt" }));
    set_weight(26700);
    init_damage(7, 14, 180, 10, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 90000);
        set("long",
            "這把重數百斤的玄鐵槌乃是勇士寒於的魂魄所化成的十三個精靈之\n"
            "一雷神「澤獸」的武器。此槌槌頭有六面，上面分別鑲有象征雷神\n"
            "六僕的六枚寶石，散發出六道耀眼的雷光纏繞在槌柄之上。\n");
        set("apply_weapon/twohanded blunt", ([
            "heavy_parry": 20,
            "taoism-thunder": 30,
            "attack": 30,
            "armor_vs_lightning": 100,
            "str": 4,
        ]));
    }
    setup();
}
