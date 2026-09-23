#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【天朝異事錄】", ({ "Strange Tales of the Celestial Court", "strange tales of the celestial court", "strange-tales-of-the-celestial-court", "strange", "tales", "celestial", "court", "book", "【天朝異事錄】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "收錄天朝各地流傳的異聞，從宮廷傳說到民間怪事，並考證故事中難解的古語。\n");
    set("required/skill", (["literate": 70, "archaic attainment": 55]));
    set("content", (["literate": 100, "archaic attainment": 80]));
    setup();
}
