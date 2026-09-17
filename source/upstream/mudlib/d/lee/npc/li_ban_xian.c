#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李半仙", ({ "li ban xian", "ban xian", "storyteller", "li", "ban", "xian" }));
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 56);
    set("long", "一位常在小旅店落腳的說書先生，鬍鬚微白，說起江湖舊聞時總是愛故意壓低聲音。目前階段只保留已經確認的角色與位置，完整的說書關鍵字和能力成長事件都待後續逐條復原。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "李半仙捻著鬍鬚，慢悠悠地打量四周。\n",
        "李半仙敲了敲桌沿，像是正想起一段很久以前的故事。\n",
    }));
    setup();
}
