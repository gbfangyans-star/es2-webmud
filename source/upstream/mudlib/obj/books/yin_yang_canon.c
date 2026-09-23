#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name(HIW "【陰陽經】" NOR, ({ "Yin Yang Canon", "yin yang canon", "yin-yang-canon", "yin", "yang", "canon", "book", "【陰陽經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "從晝夜寒暑的變化談起，推究陰陽相生相制之理，並以卦象闡明其運行法則。\n");
    set("required/skill", (["archaic attainment": 160, "mysticism": 40]));
    set("content", (["archaic attainment": 200, "mysticism": 140]));
    setup();
}
