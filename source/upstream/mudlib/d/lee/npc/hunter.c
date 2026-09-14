#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("獵戶", ({ "hunter", "lee hunter" }));
    set_race("human"); set_class("fighter"); set_level(6);
    set("age", 36);
    set("long", "村裡的獵戶，腰間掛著繩索與小刀，身上帶著山林和煙火混合的氣味。\n");
    setup();
}
