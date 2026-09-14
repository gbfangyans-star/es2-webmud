/* CUSTOM HOME SYSTEM
 * Generic developed room shell. Purpose intentionally left undefined.
 */
#include <ansi.h>
#include <room.h>

inherit ROOM;

object home_owner;
object home_hall;
int room_index;

void set_home_context(object owner, object hall, int index) {
    home_owner = owner;
    home_hall = hall;
    room_index = index;
    set("short", sprintf(HIY "家園房間 %d" NOR, room_index));
    set("long", sprintf(
        "這是你家園中已經開發完成的第%d間房。這個房間目前尚未指定用途，之後可以再進一步規劃。\n"
        HIG "可用動作：backhall 返回家園大廳。\n" NOR, room_index));
}

void create() {
    set("short", HIY "家園房間" NOR);
    set("long", "這是一間尚未指定用途的家園房間。\n");
    set("no_fight", 1);
    setup();
}

void init() {
    ::init();
    add_action("do_back", "backhall");
    add_action("do_back", "返回大廳");
}

int do_back(string arg) {
    object me;
    me = this_player();
    if (!me || me != home_owner || !home_hall)
        return notify_fail("你無法從這裡返回家園大廳。\n");
    me->move(home_hall);
    return 1;
}

int receive_object(object ob, int from_inventory) {
    if (ob->is_character() && home_owner && ob != home_owner)
        return notify_fail("這是別人的私人家園房間。\n");
    return ::receive_object(ob, from_inventory);
}
