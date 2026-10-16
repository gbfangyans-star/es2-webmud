#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name(HIW "【陰陽經】" NOR, ({ "book of advanced mysticism", "advanced", "mysticism", "canon", "book", "【陰陽經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本從上古時代流傳下來的古書﹐記錄了由天神創天地以來的種種陰陽五行間的變化。\n");
    set("required/skill", (["archaic attainment": 160, "mysticism": 40]));
    set("content", (["archaic attainment": 200, "mysticism": 140]));
    setup();
}
