

#include <command.h>
#include <skill.h>

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    int restore;
    mapping learned, flags;

    SECURED_COMMAND;

    if( !arg ) return notify_fail("你要放棄繼續學習什麼技能？\n");

    restore = sscanf(arg, "-c %s", arg) == 1;

    learned = me->query_learned();
    if( !mapp(learned) || undefinedp(learned[arg]) )
        return notify_fail("你沒有學習這項技能。\n");

    flags = me->query_skill_flags();
    if( !mapp(flags) ) flags = ([]);

    if( restore ) {
        if( !(flags[arg] & SKILL_FLAG_ABANDONED) )
            return notify_fail("你並沒有中止學習「" + to_chinese(arg) + "」。\n");
        me->abandon_skill(arg, 1);
        write("你決定恢復學習「" + to_chinese(arg) + "」。\n");
    } else {
        if( flags[arg] & SKILL_FLAG_ABANDONED )
            return notify_fail("你已經中止學習「" + to_chinese(arg) + "」了。\n");
        me->abandon_skill(arg);
        write("你決定中止學習「" + to_chinese(arg) + "」。\n");
    }
    return 1;
}

int help()
{
    write(@TEXT
指令格式：abandon <技能名稱>

這個指令讓你「中止」學習一項技能，這個技能往後不會再經由使用或學習而進步
，而且也不會出現在 skills 的列表中。但這並不表示你會完全忘記這項技能，如
果有需要，你可以用 abandon -c <技能名稱> 來恢復被你中止的技能。

中止學習的技能仍然可以使用，你可以用 skills -a 列出所有你學過的，包括正在
學習以及中止學習的技能。
TEXT
    );
    return 1;
}

