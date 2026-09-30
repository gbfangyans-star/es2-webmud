/* 血匕封喉 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_DAGGER;

void create()
{
    set_name("\x1b[0;31m血匕封喉\x1b[m", ({ "bloody dagger", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 75000);
        set("long",
            "一把帶著濃厚腥臭的血紅匕首, 匕刃極薄, 有如蝶翼。匕柄的\n"
            "部份生滿了鐵鏽, 配著薄可透光的紅刃, 更顯得陰氣森森。\n");
        set("apply_weapon/dagger", ([
            "killerhood": 10,
            "attack": 10,
            "backstab": 15,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "killerhood": 10,
            "attack": 10,
            "backstab": 15,
        ]));
    }
    setup();
}
