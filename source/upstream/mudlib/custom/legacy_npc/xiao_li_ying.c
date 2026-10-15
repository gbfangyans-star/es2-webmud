// /custom/legacy_npc/xiao_li_ying.c — 舊站 NPC：肖麗穎（Xiao li ying）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("肖麗穎", ({ "xiao li ying", "xiao", "ying" }));
    set_race("human");
    set_class("alchemist");
    set_level(25);
    set("gender", "female");
    set("age", 25);
    set("long",
        "你面前的這位女子真可謂是國色天香﹐讓人望其貌而不知色﹐聞其聲而\n"
        "不知音。這般美貌的女子天朝境內可是難得一見﹐你既然看過了﹐就該\n"
        "知足了。\n");
    set_power("A");
    setup();
    carry_object("/custom/armor/cloth/cloudy_silk_cloth")->wear();   // 雲羅絲衣
    carry_object("/custom/weapon/whip/whip_of_evil_beauties")->wield();   // 六靈妖姬鞭
}
