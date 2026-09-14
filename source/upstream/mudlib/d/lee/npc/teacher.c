#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("私塾先生", ({ "teacher", "school teacher" }));
    set_race("human"); set_class("commoner"); set_level(5);
    set("age", 49);
    set("long", "私塾裡的先生，衣著樸素，說話慢條斯理。原圖雖有私塾人物線索，但姓名與完整功能仍待核對，因此暫不用未證實的專名。\n");
    setup();
}
