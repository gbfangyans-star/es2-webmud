// withdraw.c -- global bank command bridge
inherit F_CLEAN_UP;

int main(object me, string arg)
{
    object env;

    env = environment(me);
    if( env && function_exists("do_withdraw", env) )
        return (int)env->do_withdraw(arg);

    return notify_fail("這裡不是錢莊，不能提款。\n");
}

int help(object me)
{
    write("指令格式：withdraw <數量> <貨幣種類>\n");
    return 1;
}
