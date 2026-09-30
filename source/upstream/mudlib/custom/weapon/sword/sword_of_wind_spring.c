/* 風泉之劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("風泉之劍\x1b[m", ({ "sword of wind spring", "sword" }));
    set_weight(9400);
    init_damage(3, 20, 150, 5, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "風泉之劍是步玄派掌門人的家傳配劍，劍長五尺，琉璃護手，象牙劍柄，劍身\n"
            "如鏡，透出一片淡藍色的微光。\n"
            "相傳駱步玄七十歲於練火大山的無名山谷中，誤闖風神族的聚會，和風神族的\n"
            "英雄「夜鷹」賭賽輕功，以一步之差贏得此劍。駱步玄嘗以「創步玄功」、「\n"
            "得風泉劍」、「娶吾賢妻」為自己生平三大樂事。\n");
        set("apply_weapon/sword", ([
            "parry": 20,
            "defense": 30,
        ]));
    }
    setup();
}
