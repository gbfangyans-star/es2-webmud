// /d/wutang/npc/huyen_guan.c — 五堂鎮 NPC：綠竹居士 呼延光（依五堂鎮設計表）。

#include <npc.h>
inherit F_SCHOLAR;

void create()
{
    seteuid(getuid());
    set_name("呼延光", ({ "huyen guan", "huyen", "guan" }));
    set_race("human");
    set_class("scholar");
    set_level(35);
    set("title", "綠竹居士");
    set("age", 50);
    set("long", @LONG
一位隱居在綠竹林中的居士，一襲雪白長袍，神態閒適，眉宇間透著一股
書卷氣。據說他見多識廣，天下奇聞軼事少有他不知道的，連五陵客棧的
李再延都對他推崇備至。
LONG
    );
    set_attr("str", 20);
    set_attr("cor", 25);
    set_attr("int", 30);
    set_attr("spi", 23);
    set_attr("dex", 33);
    set_attr("con", 24);
    set_attr("wis", 18);
    set_skill("unarmed", 120);
    set_skill("dodge", 90);
    set_skill("parry", 65);
    setup();
    set_stat_maximum("gin", 200);
    set_stat_effective("gin", 200);
    set_stat_current("gin", 200);
    set_stat_maximum("kee", 280);
    set_stat_effective("kee", 280);
    set_stat_current("kee", 280);
    set_stat_maximum("sen", 120);
    set_stat_effective("sen", 120);
    set_stat_current("sen", 120);
    carry_object("/custom/armor/cloth/white_cloth")->wear();
}
