#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【五數】", ({ "The Five Numbers", "the five numbers", "the-five-numbers", "five", "numbers", "book", "【五數】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "以五數為綱，記述數象之間的生剋與轉化，循淺入深推演五行陰陽的基本變化。\n");
    set("required/skill", (["literate": 50, "archaic attainment": 20]));
    set("content", (["mysticism": 20]));
    setup();
}
