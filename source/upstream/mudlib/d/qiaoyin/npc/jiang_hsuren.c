// /d/qiaoyin/npc/jiang_hsuren.c — 喬陰縣 NPC：江述仁（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("江述仁", ({ "jiang hsuren", "jiang", "hsuren" }));
    set("title", "龍圖丹派大弟子");
    set_race("human");
    set_class("alchemist");
    set_level(20);
    set("gender", "male");
    set("age", 32);
    set("long", @LONG
龍圖丹派大弟子，對丹道頗有天份，小有成就。但個性輕浮、不務正業，最近似乎捅了甚麼婁子，異常安份。
LONG
    );
    set_power("A");
    setup();
    carry_object("/obj/cloth")->wear();
}

#define ALCHEMY_FEE 500   // 柴火錢：五百文（等值貨幣、超過都可以）

// 煉丹房的柴火錢：方士給江述仁五百文以上，本次登入期間可以進出北邊的煉丹房。
int accept_object(object who, object ob)
{
    if( !ob->query("money_id") ) return 0;
    if( who->query_class() != "alchemist" ) {
        command("say 這丹房只借給方士用，閣下的錢還請收回。");
        return 0;
    }
    if( who->query_temp("qiaoyin/alchemy_paid") ) {
        command("say 你方才已經付過了，進去吧。");
        return 0;
    }
    if( ob->value() < ALCHEMY_FEE ) {
        command("say 就這麼一點？連柴火都買不起。");
        return 0;
    }
    who->set_temp("qiaoyin/alchemy_paid", 1);
    command("say 嘿嘿，好說好說，丹房就在後頭，請便。");
    return 1;
}
