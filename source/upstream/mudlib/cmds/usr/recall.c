/* CUSTOM WEBMUD RECALL COMMAND
 * User-approved convenience teleport. Not canonical ES2 gameplay content.
 */
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object dest;
    if (!me || !userp(me)) return 0;
    if (me->is_fighting()) return notify_fail("戰鬥中無法使用 recall。\n");
    if (me->is_busy()) return notify_fail("你現在沒有空使用 recall。\n");

    if (arg == "home") {
        dest = new("/custom/home/room/home_hall");
        if (!dest) return notify_fail("家園空間暫時無法開啟。\n");
        dest->set_home_owner(me);
        message_vision(HIC "$N的身影被一道柔光包圍，轉眼消失不見。\n" NOR, me);
        me->move(dest);
        tell_object(me, HIW "你回到了自己的家園。\n" NOR);
        return 1;
    }
    if (arg && arg != "") return notify_fail("指令格式：recall 或 recall home\n");

    dest = load_object("/d/snow/inn_hall");
    if (!dest) return notify_fail("客棧目前無法抵達。\n");
    message_vision(HIC "$N的身影被一道柔光包圍，轉眼消失不見。\n" NOR, me);
    me->move(dest);
    tell_object(me, HIW "你回到了客棧。\n" NOR);
    return 1;
}

int help(object me)
{
    write("指令格式：recall / recall home\nrecall 回到雪亭客棧；recall home 回到自己的私人家園。\n戰鬥或忙碌中不可使用。\n");
    return 1;
}
