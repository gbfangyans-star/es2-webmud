// open.c

#include <room.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping doors;
	string *dirs, dir;
	int i;
	object env;

	if( !arg ) return notify_fail("你要打開什麼﹖\n");

	env = environment(me);
	// 錢莊的開戶語法沿用「open account」。由於 open 同時也是
	// 全域開門指令，先把 account 明確轉交給銀行房間，避免被
	// 開門指令攔截而無法執行 std/room/bank.c::do_new_account()。
	if( arg == "account" && env && function_exists("do_new_account", env) )
		return (int)env->do_new_account(arg);

	doors = env->query_doors();
	if( mapp(doors) ) {
		dirs = keys(doors);
		if( member_array(arg, dirs)!=-1 ) dir = arg;
		else for(i=0; i<sizeof(dirs); i++)
			if( arg==doors[dirs[i]]["name"] || member_array(arg, doors[dirs[i]]["id"])!=-1 ) {
				dir = dirs[i];
				break;
			}
		if( !dir ) return notify_fail("你要打開什麼﹖\n");
	
		if( environment(me)->open_door(dir) ) {
			tell_object(me, "你將" + doors[dir]["name"] + "打開。\n");
			tell_room(environment(me), me->name() + "將" + doors[dir]["name"] + "打開。\n", ({ me }));
			return 1;
		}
	}

	return 0;
}

int help(object me)
{
        write(@HELP
指令格式 : open <door> 或 <方向>
 
這個指令可以讓你打開門.
 
HELP
    );
    return 1;
}
