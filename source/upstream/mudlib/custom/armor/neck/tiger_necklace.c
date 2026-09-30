/* 虎牙項鏈 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;37m虎牙項鏈\x1b[m", ({ "tiger necklace", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 15000);
        set("long",
            "一串用鋒利的白色虎齒做成的項鏈，似乎充滿了某種神秘的力量。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "cor": 2,
            "damage": 10,
        ]));
    }
    setup();
}
