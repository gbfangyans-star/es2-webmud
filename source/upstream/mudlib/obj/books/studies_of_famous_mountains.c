#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【名山文考】", ({ "Studies of Famous Mountains", "studies of famous mountains", "studies-of-famous-mountains", "studies", "famous", "mountains", "book", "【名山文考】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "考辨名山石刻、碑銘與舊籍記載，從殘缺文字中追索山川名稱和歷代傳說。\n");
    set("required/skill", (["literate": 40, "archaic attainment": 20]));
    set("content", (["literate": 80, "archaic attainment": 50]));
    setup();
}
