/* CUSTOM HOME SYSTEM - private study room.
 * User-approved WebMUD extension. Not canonical ES2 content.
 */
#include <ansi.h>
#include <room.h>

inherit ROOM;

object home_owner;
object home_hall;
int room_index;

void set_home_context(object owner, object hall, int idx) {
    home_owner = owner;
    home_hall = hall;
    room_index = idx;
    set("short", HIY "書房" NOR);
    set("long",
        "這是一間安靜的私人書房。靠牆立著木製書架，中央擺著寬大的書桌與座椅，燈火被罩得柔和而穩定。\n"
        "這裡少有外界干擾，很適合靜下心來研讀書籍與卷冊。\n"
        HIG "在此使用原本的 study 指令研讀時，學習效率提升 20%；backhall 返回家園大廳。\n" NOR);
    set("custom_home/study_bonus", 120);
}

void create() {
    set("short", HIY "書房" NOR);
    set("long", "一間安靜的私人書房。\n");
    set("no_fight", 1);
    set("custom_home/study_bonus", 120);
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
    me->move(home_hall);
    return 1;
}

int receive_object(object ob, int from_inventory) {
    if (ob->is_character() && home_owner && ob != home_owner)
        return notify_fail("這是別人的私人家園房間。\n");
    return ::receive_object(ob, from_inventory);
}
