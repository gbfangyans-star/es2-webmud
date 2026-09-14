/* CUSTOM HOME SYSTEM - development board.
 * User-approved WebMUD extension. Not canonical ES2 content.
 */
#include <ansi.h>

inherit ITEM;

object home_owner;

void set_home_owner(object ob) { home_owner = ob; }

void create() {
    set_name(HIY "家園告示板" NOR, ({ "development board", "board", "告示板", "家園告示板" }));
    set_weight(1000000);
    set("unit", "面");
    setup();
}

string room_menu(int rooms) {
    int next_room, price;
    string s;

    next_room = rooms + 1;
    price = next_room * 10;

    s = HIY "【增建房間】\n" NOR;
    s += sprintf("目前已增建：%d / 10 間\n", rooms);
    if (rooms < 10)
        s += sprintf(HIC "本次將增建第 %d 間，費用：%d GOLD\n\n" NOR, next_room, price);
    else
        s += HIG "目前十間家園房間均已開發完成。\n\n" NOR;

    s += HIG "1. 寢室" NOR "　有床可以上床休息，每分鐘恢復精／氣／神各 10%。\n";
    s += HIG "2. 書房" NOR "　在書房內研讀，讀書學習效率提升 20%。\n";
    s += "3. 尚未開放\n";
    s += "4. 尚未開放\n";
    s += "5. 尚未開放\n";

    if (rooms < 10)
        s += HIY "\n選擇方式：select 1-5　或　選擇 1-5\n" NOR;
    return s;
}

string long(int raw) {
    int rooms;
    string s;

    rooms = home_owner ? (int)home_owner->query("custom_home/rooms") : 0;
    if (rooms < 0) rooms = 0;
    if (rooms > 10) rooms = 10;

    s = "一面整齊的木製告示板，上頭把家園增建項目一列一列寫得十分清楚。\n\n";
    s += room_menu(rooms);
    return s;
}

void init() {
    add_action("do_select", "select");
    add_action("do_select", "選擇");
    add_action("do_select", "develop");
    add_action("do_select", "增建");
}

int do_select(string arg) {
    object me;
    int rooms, gold_cost, cost, n, choice;
    string type, cname;

    me = this_player();
    if (!me || me != home_owner)
        return notify_fail("這面告示板只接受家園主人的增建申請。\n");

    /* Backward-compatible text aliases from v3.20.17. */
    if (arg == "bedroom" || arg == "寢室") choice = 1;
    else if (arg == "study" || arg == "study room" || arg == "書房") choice = 2;
    else if (!arg || sscanf(arg, "%d", choice) != 1)
        return notify_fail("請先 look board，再用 select <編號> 或 選擇 <編號>。\n");

    if (choice < 1 || choice > 5)
        return notify_fail("請選擇告示板上列出的 1 到 5 號房型。\n");
    if (choice >= 3)
        return notify_fail("這個房型目前尚未開放。\n");

    rooms = (int)me->query("custom_home/rooms");
    if (rooms < 0) rooms = 0;
    if (rooms >= 10)
        return notify_fail("你的家園已經開發十間房間，暫時無法繼續增建。\n");

    n = rooms + 1;
    gold_cost = n * 10;
    cost = gold_cost * 10000;
    if ((int)me->can_afford(cost) != 1)
        return notify_fail(sprintf("增建第%d間房需要%d GOLD。\n", n, gold_cost));

    if (choice == 1) {
        type = "bedroom";
        cname = "寢室";
    } else {
        type = "study_room";
        cname = "書房";
    }

    me->pay_money(cost);
    me->set("custom_home/rooms", n);
    me->set(sprintf("custom_home/room_type/%d", n), type);
    me->save();

    tell_object(me, sprintf(HIY "你在告示板上選定「%s」，付清%d GOLD。家園深處傳來木石落定的聲響。\n" NOR,
        cname, gold_cost));
    tell_object(me, sprintf(HIG "第%d間家園房間已增建為%s，可用 enter %d 進入。\n" NOR,
        n, cname, n));
    return 1;
}

int move(mixed dest) {
    if (objectp(dest) && dest->is_character()) return 0;
    return ::move(dest);
}
