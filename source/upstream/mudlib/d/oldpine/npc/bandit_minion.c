// /d/oldpine/npc/bandit_minion.c — 老松林 NPC：土匪嘍囉（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


// 看到玩家就下殺手（kill），玩家昏倒後也會繼續攻擊直到死亡。
void init()
{
    object ob = this_player();

    ::init();
    if( objectp(ob) && userp(ob) && living(this_object()) && !is_fighting(ob)
    &&  !environment()->query("no_fight") && visible(ob) ) {
        message_vision("$N扯著嗓子大喊：「打、打劫！把值錢的東西統統交出來！」\n", this_object());
        kill_ob(ob);
    }
}

void create()
{
    seteuid(getuid());
    set_name("土匪嘍囉", ({ "bandit minion", "minion", "bandit" }));
    set_race("human");
    set_class("thief");
    set_level(5);
    set("long", @LONG
看起來沒啥江湖經驗，努力裝兇卻顯得異常可笑。
LONG
    );
    set_skill("blade", 10);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    set_skill("unarmed", 10);
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 5 ]));
    setup();
    set_stat_maximum("gin", 60);
    set_stat_effective("gin", 60);
    set_stat_current("gin", 60);
    set_stat_maximum("kee", 75);
    set_stat_effective("kee", 75);
    set_stat_current("kee", 75);
    set_stat_maximum("sen", 35);
    set_stat_effective("sen", 35);
    set_stat_current("sen", 35);
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/custom/armor/cloth/leather_vest")->wear();
    carry_money("silver", 2);
}
