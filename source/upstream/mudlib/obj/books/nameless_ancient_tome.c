#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【無名古籍】", ({ "Nameless Ancient Tome", "nameless ancient tome", "nameless-ancient-tome", "nameless", "ancient", "tome", "book", "【無名古籍】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "書頁殘破且不見作者姓名，零散篇章卻暗藏古老術理，須反覆考讀才能連起線索。\n");
    set("required/skill", (["archaic attainment": 120, "mysticism": 150]));
    set("content", (["archaic attainment": 160, "mysticism": 185]));
    setup();
}
