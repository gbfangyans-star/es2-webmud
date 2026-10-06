/*---
description: 定義留言板相關功能。
author: Annihilator <taedlar@gmail.com>
---*/

#include <ansi.h>

#define	BOARD_CAPACITY	query("capacity")
#define	NO_PLAYER_POST	query("NO_PLAYER_POST")
// 發文需要的最低巫師等級（見 securityd 的 wiz_levels：1 immortal、2 apprentice、3 wizard…）。
#define	POST_WIZ_LEVEL	query("post_wiz_level")

inherit ITEM;
inherit F_SAVE;

private string usage = "你可以在留言板使用以下命令：\n"
"\t" UNDL "post" NOR " <標題>\n"
"\t" UNDL "read" NOR " new|next|<編號>\n"
"\t" UNDL "discard" NOR " <標題>\n"
"\t" UNDL "followup" NOR " <編號> <標題>\n"
;

void
setup()
{
    string loc;

    seteuid(getuid());
    ::setup();
    if( stringp(loc = query("location")) )
        move(loc);
    set("no_get", 1);
    restore();
}

private void
init()
{
    add_action("do_help", "help");
    add_action("do_post", "post");
    add_action("do_read", "read");
    add_action("do_discard", "discard");
    add_action("do_save_article", "save");
    add_action("do_followup", "followup");
}

string
query_save_file()
{
    string id;

    if( !stringp(id = query("board_id")) ) return 0;
    return DATA_DIR + "board/" + id + ".o";
}

// 已讀紀錄：每個留言板記下讀過的留言時間（留言的時間就是它的識別）。
// 原本只記「讀過最新那篇的時間」，先讀了後面的留言，read new 就會跳過前面還沒讀的。
private mixed *read_list(object me)
{
    mixed r;
    if( !me || !me->link() ) return ({});
    r = me->link()->query("board_read/" + (string)query("board_id"));
    return arrayp(r) ? r : ({});
}

int note_is_read(object me, int time)
{
    return member_array(time, read_list(me)) != -1;
}

private void mark_read(object me, int time)
{
    mapping *notes = query("notes");
    mixed *list, *keep = ({});
    int i;

    if( !me || !me->link() ) return;
    list = read_list(me);
    if( member_array(time, list) == -1 ) list += ({ time });
    // 只保留目前還在板上的留言，紀錄不會無限變大。
    if( pointerp(notes) )
        for(i = 0; i < sizeof(notes); i++)
            if( member_array(notes[i]["time"], list) != -1 ) keep += ({ notes[i]["time"] });
    me->link()->set("board_read/" + (string)query("board_id"), keep);
}

string
short()
{
    mapping *notes;
    int i, unread, last_read_time;

    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
        return ::short() + " [沒有任何留言]";

    if( this_player() && this_player()->link() )
        for(i = 0; i < sizeof(notes); i++)
            if( !note_is_read(this_player(), notes[i]["time"]) ) unread++;
    if( unread )
        return sprintf("%s [%d 張留言﹐%d 張未讀]", ::short(), sizeof(notes), unread);
    else
        return sprintf("%s [%d 張留言]", ::short(), sizeof(notes));
}

string
long()
{
    mapping *notes;
    int i, last_time_read;
    string msg;

    notes = query("notes");
    msg = query("long");
    if( !msg ) msg = "";
    if( !pointerp(notes) || !sizeof(notes) )
        return msg += query("name") + "使用方法請見 help board，留言板約可容納 " +BOARD_CAPACITY+ " 篇留言。\n";

    // 未讀的留言編號以亮黃色標示；標題、作者依畫面寬度對齊。
    for(i=0; i<sizeof(notes); i++)
        msg += sprintf("%s[%2d]" NOR "  %s %s - %s\n",
            ( note_is_read(this_player(), notes[i]["time"]) ? "" : HIY ),
            i+1,
            cjk_pad(notes[i]["title"], 34),
            cjk_pad(notes[i]["author"], 22, 1),
            ctime(notes[i]["time"])[0..9]
        );
    return msg += "\n=== " + query("name") + "使用方法請見 help board，留言版約可容納 " +BOARD_CAPACITY+ " 篇留言 ===\n";
}

int
do_help(string arg)
{
  if (arg != "board")
    return 0;

  write(usage);
  return 1;
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void
done_post(object me, mapping note, string text)
{
    mapping *notes;
    string sig;

    if( stringp(sig = me->link()->query("signature")) )
        text += "--\n" + sig;   // 加 -- 好在 followup 可以知道
    note["msg"] = text;
    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
        notes = ({ note });
    else
        notes += ({ note });

    // Truncate the notes if maximum capacity exceeded.
    if( sizeof(notes) > BOARD_CAPACITY )
        notes = notes[BOARD_CAPACITY / 4 .. BOARD_CAPACITY];

    set("notes", notes);
    tell_object(me, "留言完畢。\n");

    save();
    return;
}

int
do_post(string arg)
{
    mapping note;
    if(!arg) return notify_fail("留言請指定一個標題。\n");

    // add by ueiren ..
    if ( POST_WIZ_LEVEL && wiz_level(this_player()) < POST_WIZ_LEVEL )
        return notify_fail("只有巫師才能在這個公佈欄張貼。\n");
    if ( NO_PLAYER_POST && (!wizardp(this_player())))
    return notify_fail("玩家不可在此公佈欄留言。\n");

    if( strlen(arg) > 40 )
        return notify_fail("您的標題太長了﹐換一個 40 個字元以內的吧。\n");
        
    note = allocate_mapping(4);
    note["title"] = arg;
    note["author"] = this_player()->name() + "(" +this_player()->query("id") + ")";
    note["time"] = time();
    this_player()->edit( (: done_post, this_player(), note :) );
    return 1;
}

int
do_read(string arg)
{
    int num,tmp;
    mapping *notes, last_read_time;
    string myid;

    last_read_time = this_player()->link()->query("board_last_read");
    myid = query("board_id");
    notes = query("notes");

    if( !pointerp(notes) || !sizeof(notes) )
        return notify_fail("留言板上目前沒有任何留言。\n");

    if( !arg ) return notify_fail("指令格式﹕read <留言編號>|new|next\n");
    if( arg=="new" || arg=="next" ) {
        // 從編號最小、還沒讀過的留言開始，一次讀一篇。
        for(num = 1; num<=sizeof(notes); num++)
            if( !note_is_read(this_player(), notes[num-1]["time"]) ) break;
        // 全部都讀過了：明確告訴玩家沒有新留言，而不是「沒有這張留言」。
        if( num > sizeof(notes) )
            return notify_fail("目前沒有新的留言﹐要重讀請用 read <編號>。\n");
    } else if( !sscanf(arg, "%d", num) )
        return notify_fail("你要讀第幾張留言﹖\n");

    if( num < 1 || num > sizeof(notes) )
        return notify_fail("沒有這張留言。\n");
    num--;
    // 標題、作者依畫面寬度補空白（sprintf 會把中文字算成 3 格，標題長短不同時作者欄就對不齊）。
    this_player()->start_more_if_needed (sprintf("[%2d]  %s %s%s%s%s\n",
        num + 1,
        cjk_pad(notes[num]["title"], 34),
        cjk_pad(notes[num]["author"], 26, 1),
        "(" + ctime(notes[num]["time"])[0..9] + ")",
        "\n---------------------------------------------------------------------------\n",
        notes[num]["msg"]));

    // Keep track which post we were reading last time.
    // 登入物件的 query() 回傳的是 mapping 的複本，直接改 last_read_time 不會存回去
    // （以前只有第一次讀留言板時記得住，之後未讀數不會減少、read new 一直停在舊文章）；
    // 一律用 set() 寫回。
    if( !mapp(last_read_time) )
        this_player()->link()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
    else if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
        this_player()->link()->set("board_last_read/" + myid, notes[num]["time"]);
    // 逐篇已讀紀錄（read new 與未讀標示用這個）。
    mark_read(this_player(), notes[num]["time"]);

    return 1;
}


int
do_discard(string arg)
{
    mapping *notes;
    int num;

    if( !arg || sscanf(arg, "%d", num)!=1 )
        return notify_fail("指令格式﹕discard <留言編號>\n");
    notes = query("notes");
    if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
        return notify_fail("沒有這張留言。\n");
    num--;
    if( notes[num]["author"] != (string) this_player(1)->query("name")+ "(" + this_player(1)->query("id") + ")"
    &&	wiz_level(this_player(1)) < 4 )
        return notify_fail("這個留言不是你寫的。\n");

    notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
    set("notes", notes);
    save();
    write("刪除第 " + (num+1) + " 號留言....Ok。\n");
    return 1;
}

int
do_save_article(string arg)
{
    int num;
    string file;
    mapping *notes;

    if( !wizardp(this_player()) ) return 0;
    if( !arg || sscanf(arg, "article %d to %s", num, file)!=2 ) return 0;
        
    if( !arrayp(notes = query("notes"))
    ||	num<1
    ||	num>sizeof(notes) )
        return notify_fail("沒有這張留言。\n");
    num--;
    file = resolve_path(this_player()->query("cwd"), file);
    if( write_file(file, notes[num]["msg"]) )
        write("Ok.\n");
    else
        return notify_fail("儲存失敗。\n");
    return 1;
}

int
do_followup(string str)
{
    mapping *notes, note;
    string *text, title;
    int i, num;
        
    // add by dragoon
    if ( POST_WIZ_LEVEL && wiz_level(this_player()) < POST_WIZ_LEVEL )
        return notify_fail("只有巫師才能在這個公佈欄張貼。\n");
    if ( NO_PLAYER_POST && (!wizardp(this_player())))
        return notify_fail("玩家不可在此公佈欄留言。\n");

    if( !str )
        return notify_fail("指令格式﹕followup <留言編號> [新的標題]\n");

    if( sscanf(str, "%d %s", num, title) != 2 )
        if( sscanf(str, "%d", num) != 1 )
            return notify_fail("你要回第幾篇的留言﹖\n");
        
    notes = query("notes");
        
    if( num < 1 || num > sizeof(notes) )
        return notify_fail("沒有這篇留言。\n");

    num--;
    if( !title ) title = "Re﹕" + notes[num]["title"];
    note = allocate_mapping(4);
    note["title"]  = title;
    note["author"] = this_player()->query("name") + "(" + this_player()->query("id") + ")";
    note["time"]   = time();

    text = explode( notes[num]["msg"], "\n" );
    // title, num 這兩個變數拿來再利用
    title = sprintf(GRN"> %s 在 %s 留下這篇留言﹕\n"NOR,
        notes[num]["author"],
        "(" + ctime(notes[num]["time"])[0..9] + ")" );

    num = sizeof(text);
    for( i=0; i<num; i++ ) 
    {
        // 空行跳過, 上上一篇跳過
        if( text[i] == "" || strsrch(text[i], "> ") != -1)
            continue;
        // 簽名檔, 結束
        if( text[i][0..1] == "--" )
            i=num;
        else title = title + GRN + "> " + text[i] + NOR + "\n";
    }
    note["msg"] = title;
    this_player()->edit( (: done_post, this_player(), note :), title );
    return 1;
}
