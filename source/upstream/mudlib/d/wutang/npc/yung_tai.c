// /d/wutang/npc/yung_tai.c — 五堂鎮 NPC：雍泰（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("雍泰", ({ "yung tai", "yung", "tai" }));
    set_race("yenhold");
    set_class("fighter");
    set_level(20);
    set("age", 30);
    set("long", @LONG
雍泰是五堂鎮雍家這一代的老三﹐自從前年雍老爺從斐縣官期任滿
回鄉中途不幸被盜匪殺害﹐雍家四個兒子便流離各處﹐雍泰是幾個
月前才得到同鄉好友景襄仁景二爺幫助才得以湊足盤纏扶著老父棺
木回鄉安葬﹐雍家世代或為文官﹐或為武將﹐都是兩袖清風﹐家財
向來不富﹐但是卻相當受到五堂鎮居民的敬重﹐想不到這一代遭逢
厄運﹐眼看著就要沒落了。
LONG
    );
    set_attr("str", 35);
    set_attr("cor", 30);
    set_attr("cps", 30);
    set_attr("dex", 35);
    set_attr("con", 32);
    set_skill("unarmed", 40);
    set_skill("dodge", 40);
    set_skill("parry", 40);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "雍泰獨自坐在角落喝著悶酒，望著窗外的鐵旗桿怔怔出神。\n",
        "雍泰嘆了口氣：「先父一生清廉，到頭來卻落得這般下場……」\n",
    }));
    setup();
    set_stat_maximum("gin", 240);
    set_stat_effective("gin", 240);
    set_stat_current("gin", 240);
    set_stat_maximum("kee", 300);
    set_stat_effective("kee", 300);
    set_stat_current("kee", 300);
    set_stat_maximum("sen", 100);
    set_stat_effective("sen", 100);
    set_stat_current("sen", 100);
}
