// /d/oldpine/npc/bandit.c — 老松林 NPC：土匪（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


// 看到玩家就下殺手（kill），玩家昏倒後也會繼續攻擊直到死亡。
void init()
{
    object ob = this_player();

    ::init();
    if( objectp(ob) && userp(ob) && living(this_object()) && !is_fighting(ob)
    &&  !environment()->query("no_fight") && visible(ob) ) {
        message_vision("$N一聲怒吼「殺～～～～～」，隨即發起瘋狂的進攻！\n", this_object());
        kill_ob(ob);
    }
}

void create()
{
    seteuid(getuid());
    set_name("土匪", ({ "bandit" }));
    set_race("human");
    set_class("thief");
    set_level(10);
    set("age", 30);
    set("long", @LONG
滿臉橫肉看起來一副凶神惡煞的樣子。
LONG
    );
    set_skill("blade", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    set_skill("unarmed", 20);
    // 擊殺者獲得戰場功勳。
    set("bounty", ([ "military service": 15 ]));
    setup();
    set_stat_maximum("gin", 120);
    set_stat_effective("gin", 120);
    set_stat_current("gin", 120);
    set_stat_maximum("kee", 150);
    set_stat_effective("kee", 150);
    set_stat_current("kee", 150);
    set_stat_maximum("sen", 50);
    set_stat_effective("sen", 50);
    set_stat_current("sen", 50);
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/custom/armor/cloth/leather_vest")->wear();
    carry_money("silver", 5);
}
