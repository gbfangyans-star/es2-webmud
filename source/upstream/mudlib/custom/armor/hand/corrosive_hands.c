/* 腐蝕之手 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

// 腐蝕之手：戴著時 corrupt <屍體>，把 NPC 的屍體化成碎銀，
// 銀兩 10 ～（慧根＋定力）× 3 兩；屍體身上的東西掉在原地。玩家的屍體不行。
void init()
{
    if( this_player() == environment() )
        add_action("do_corrupt", "corrupt");
}

int do_corrupt(string arg)
{
    object me = this_player(), corpse, where, silver, inv;
    int top, amount;

    if( !arg || environment() != me ) return 0;
    if( !query("equipped") )
        return notify_fail("你得先把" + name() + "戴上。\n");
    if( !objectp(corpse = present(arg, environment(me)))
    &&  !objectp(corpse = present(arg, me)) )
        return notify_fail("這裡沒有這樣東西。\n");
    if( !corpse->is_corpse() )
        return notify_fail(corpse->name() + "不是屍體。\n");
    if( corpse->query("player_corpse") )
        return notify_fail("一股莫名的力量阻止了你，玩家的屍體碰不得。\n");

    where = environment(corpse);
    foreach(inv in all_inventory(corpse)) inv->move(where);

    top = (me->query_attr("wis") + me->query_attr("cps")) * 3;
    amount = top > 10 ? 10 + random(top - 9) : 10;
    message_vision("$N伸出正在腐爛的雙手，摸了$n一下，伴隨著一股惡臭的黑煙，$n只剩下一些碎銀。\n", me, corpse);
    silver = new("/obj/money/silver");
    silver->set_amount(amount);
    destruct(corpse);
    silver->move(where);
    return 1;
}


void create()
{
    set_name("腐蝕之手", ({ "corrosive hands", "hands" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 15000);
        set("long",
            "一雙 ... 正在腐爛的 ... 手？真的要當手套戴嗎，嘔 ... 嘔 ... (corrupt)\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "cps": 5,
            "armor": 50,
        ]));
    }
    setup();
}
