#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李嘯天", ({ "lee xiao tian", "li xiao tian", "manager lee" }));
    set_race("human");
    set_class("commoner");
    set_level(8);
    set("age", 41);
    set("long", "李員外家的二總管，也是李記當鋪的掌櫃。舊資料確定此處兼做買賣與典當；目前先保留人物與地點，等原典當規則核對後再接上正式估價與贖回流程。\n");
    set("chat_chance", 1);
    set("chat_msg", ({ "李嘯天低頭翻著帳簿，偶爾撥動算盤珠。\n" }));
    setup();
}
