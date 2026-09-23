#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【十三靈頌】", ({ "Verses of the Thirteen Spirits", "verses of the thirteen spirits", "verses-of-the-thirteen-spirits", "verses", "thirteen", "spirits", "book", "【十三靈頌】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "記載傳說中十三靈的來歷、形貌與特性，以頌文和註解整理彼此相關的傳說。\n");
    set("required/skill", (["literate": 60, "archaic attainment": 40]));
    set("content", (["literate": 100, "archaic attainment": 100]));
    setup();
}
