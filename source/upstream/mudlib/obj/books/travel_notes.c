#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【遊歷雜記】", ({ "Travel Notes", "travel notes", "travel-notes", "travel", "notes", "book", "【遊歷雜記】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "作者沿途記下山川道路、城鎮風物與旅人見聞，字句平實，適合初學識字的人逐篇閱讀。\n");
    set("content", (["literate": 35]));
    setup();
}
