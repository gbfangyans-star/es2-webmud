// /d/wutang/npc/guard.c — 五堂鎮 NPC：護院武師（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("護院武師", ({ "guard" }));
    set_race("blackteeth");
    set_class("fighter");
    set_level(20);
    set("age", 20);
    set("long", @LONG
肌肉虯結一身橫肉，看起來並不好惹的樣子。
LONG
    );
    set_skill("unarmed", 40);
    set_skill("blade", 40);
    set_skill("dodge", 40);
    set_skill("parry", 40);
    set_power("B");
    setup();
    carry_object("/custom/armor/cloth/cowhide_vest")->wear();
    carry_object("/obj/area/obj/blade")->wield();
}
