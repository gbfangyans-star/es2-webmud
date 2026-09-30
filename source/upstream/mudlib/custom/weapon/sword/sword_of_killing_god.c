/* 蔑天劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("蔑天劍", ({ "sword of killing god", "sword" }));
    set_weight(19000);
    init_damage(3, 22, 140, 4, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把充滿詛咒的邪惡之刃﹐劍名蔑天﹐意為配用此劍之人定有殺神斬鬼\n"
            "之傲氣﹐上不敬天神﹐下無視鬼怪。\n");
        set("apply_weapon/twohanded sword", ([
            "damage": 30,
            "cor": 3,
            "cps": -5,
            "twohanded sword": 15,
        ]));
    }
    setup();
}
