/* CUSTOM HOME SYSTEM - private bedroom.
 * User-approved WebMUD extension. Not canonical ES2 content.
 */
#include <ansi.h>
#include <room.h>

inherit ROOM;

object home_owner;
object home_hall;
object bed;
int room_index;

void set_home_context(object owner, object hall, int idx) {
    home_owner = owner;
    home_hall = hall;
    room_index = idx;
    set("short", HIY "寢室" NOR);
    set("long",
        "這是一間屬於你的私人寢室。木牆隔去了外面的聲響，燈火柔和，室內收拾得乾淨整齊。\n"
        "靠牆擺著一張鋪好被褥的床，疲倦時可以上床安靜休息。\n"
        HIG "look bed 查看床；rest bed 或 上床開始休息；backhall 返回家園大廳。\n" NOR);
    if (!bed) {
        bed = new("/custom/home/obj/bed");
        bed->move(this_object());
    }
}

void create() {
    set("short", HIY "寢室" NOR);
    set("long", "一間安靜的私人寢室。\n");
    set("no_fight", 1);
    setup();
}

void init() {
    ::init();
    add_action("do_backhall", "backhall");
    add_action("do_backhall", "返回大廳");
}

int do_backhall(string arg) {
    object me;
    me = this_player();
    if (!me || me != home_owner || !home_hall)
        return notify_fail("你無法從這裡返回家園大廳。\n");
    me->delete("custom_home/bed_resting");
    me->move(home_hall);
    return 1;
}

int receive_object(object ob, int from_inventory) {
    if (ob->is_character() && home_owner && ob != home_owner)
        return notify_fail("這是別人的私人家園房間。\n");
    return ::receive_object(ob, from_inventory);
}
