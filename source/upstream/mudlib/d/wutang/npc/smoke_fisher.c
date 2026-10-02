// /d/wutang/npc/smoke_fisher.c — 五堂鎮 NPC：煙波釣叟（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("煙波釣叟", ({ "fisher", "smoke fisher" }));
    set_race("human");
    set_class("fighter");
    set_level(50);
    set("age", 70);
    set("long", @LONG
看起來在這裡但感覺不到他在這裡，只見一翁一竿在草船上坐著，彷彿時間就這樣停止了。
LONG
    );
    set_attr("str", 25);
    set_attr("cor", 35);
    set_attr("int", 22);
    set_attr("spi", 16);
    set_attr("cps", 32);
    set_skill("unarmed", 100);
    set_skill("dodge", 100);
    set_skill("parry", 100);
    set_skill("whip", 100);
    setup();
    set_stat_maximum("gin", 800);
    set_stat_effective("gin", 800);
    set_stat_current("gin", 800);
    set_stat_maximum("kee", 600);
    set_stat_effective("kee", 600);
    set_stat_current("kee", 600);
    set_stat_maximum("sen", 400);
    set_stat_effective("sen", 400);
    set_stat_current("sen", 400);
    carry_object("/custom/weapon/whip/silk_fishing_stick")->wield();
    carry_object("/custom/armor/cloth/straw_cloth")->wear();
}
