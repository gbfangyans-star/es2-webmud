#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("黃山對弈譜", ({ "Yellow Mountain Chess Manual", "yellow mountain chess manual", "yellow-mountain-chess-manual", "yellow", "mountain", "chess", "manual", "book", "黃山對弈譜" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "收錄棋局與攻守變化，從落子布局到殘局應對，逐步解說對弈時的思路。\n");
    set("required/skill", (["literate": 10]));
    set("content", (["literate": 15]));
    setup();
}
