// /custom/legacy_npc/han_wen_suei.c — 舊站 NPC：韓文緒（Han wen-suei）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：喬陰縣；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("韓文緒", ({ "han wen-suei", "han", "wen-suei" }));
    set("title", "喬陰縣督護衛");
    set_race("yenhold");
    set_class("soldier");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "韓文緒是喬陰縣城的都護衛，負責喬陰縣的軍務工作，他的武藝雖然還\n"
        "稱不上一流高手，但是家傳的韓家槍法倒也已有八九分火候，在江湖上\n"
        "頗有些名頭。\n");
    set_power("B");
    setup();
    carry_object("/d/snow/npc/obj/clothboot")->wear();   // 皂步靴
    carry_object("/custom/armor/cloth/cyan_cloth")->wear();   // 青布官服
    carry_object("/custom/weapon/pike/thunder_pike")->wield();   // 紫電紅纓槍
    carry_object("/custom/armor/head/battle_helm")->wear();   // 步軍戰盔
    carry_object("/custom/armor/armor/battle_armor")->wear();   // 步軍戰鎧
    carry_object("/obj/cloth")->wear();   // 布衣
}
