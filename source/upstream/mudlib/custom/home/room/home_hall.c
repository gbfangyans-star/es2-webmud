/* CUSTOM HOME SYSTEM
 * Per-player private home entrance hall.
 * WebMUD extension. Not part of taedlar/es2_mudlib canonical content.
 */
#include <ansi.h>
#include <room.h>

inherit ROOM;

object home_owner;
object chest;
object butler;
object board;

void set_home_owner(object ob) {
    home_owner = ob;

    if (!chest) {
        chest = new("/custom/home/obj/storage_chest");
        chest->set_home_owner(ob);
        chest->move(this_object());
    }
    if (!butler) {
        butler = new("/custom/home/npc/butler");
        butler->set_home_owner(ob);
        butler->move(this_object());
    }
    if (!board) {
        board = new("/custom/home/obj/development_board");
        board->set_home_owner(ob);
        board->move(this_object());
    }
}

void create() {
    set("short", HIY "家園大廳" NOR);
    set("long",
        "這裡是只屬於你的私人家園入口大廳。空間安靜而穩定，現在仍保持著最初的簡潔模樣。\n"
        "大廳中放著一只私人儲物箱，旁邊站著家園管家，牆上新掛了一面列有增建房型的告示板。\n"
        HIG "可用動作：returnhome 返回雪亭客棧；look chest 查看儲物箱；look board 查看增建告示板。\n" NOR);
    set("no_fight", 1);
    setup();
}

string long(int raw) {
    int rooms;
    string s;
    rooms = home_owner ? (int)home_owner->query("custom_home/rooms") : 0;
    s = "這裡是只屬於你的私人家園入口大廳。空間安靜而穩定，現在仍保持著最初的簡潔模樣。\n"
        "大廳中放著一只私人儲物箱，旁邊站著家園管家，牆上新掛了一面列有增建房型的告示板。\n";
    s += sprintf("目前已開發房間：%d / 10\n", rooms);
    if (rooms > 0)
        s += HIG "進入已開發房間：enter <1-10>\n" NOR;
    s += HIG "returnhome 返回雪亭客棧；look chest 查看儲物箱；look board 查看增建告示板。\n" NOR;
    return s;
}

void init() {
    ::init();
    add_action("do_return", "returnhome");
    add_action("do_return", "返回客棧");
    add_action("do_enter_room", "enter");
    add_action("do_enter_room", "進入");
}

int do_enter_room(string arg) {
    object me, room;
    int n, rooms;

    me = this_player();
    if (!me || me != home_owner)
        return notify_fail("這裡不是你的家園。\n");
    if (!arg || sscanf(arg, "%d", n) != 1)
        return notify_fail("指令：enter <房間編號>\n");

    rooms = (int)me->query("custom_home/rooms");
    if (n < 1 || n > rooms || n > 10)
        return notify_fail("這個家園房間尚未開發。\n");

    if ((string)me->query(sprintf("custom_home/room_type/%d", n)) == "bedroom")
        room = new("/custom/home/room/bedroom");
    else if ((string)me->query(sprintf("custom_home/room_type/%d", n)) == "study_room")
        room = new("/custom/home/room/study_room");
    else
        room = new("/custom/home/room/future_room");
    if (!room) return notify_fail("家園房間暫時無法開啟。\n");
    room->set_home_context(me, this_object(), n);
    me->move(room);
    return 1;
}

int do_return(string arg) {
    object me;
    me = this_player();
    if (!me || me != home_owner)
        return notify_fail("這裡不是你的家園。\n");

    tell_object(me, HIC "家園空間泛起一道光，你回到了飲風客棧。\n" NOR);
    me->move("/d/snow/inn_hall");
    return 1;
}

int receive_object(object ob, int from_inventory) {
    if (ob->is_character() && home_owner && ob != home_owner)
        return notify_fail("一道無形屏障阻止你進入別人的私人家園。\n");
    return ::receive_object(ob, from_inventory);
}
