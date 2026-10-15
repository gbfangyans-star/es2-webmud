// /custom/legacy_npc/yu_tieshan.c — 舊站 NPC：魚鐵山（Yu tieshan）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：雪吟莊；房間：雪吟莊大廳。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("魚鐵山", ({ "yu tieshan", "yu", "tieshan" }));
    set("title", "雪吟莊莊主");
    set_race("human");
    set_class("fighter");
    set_level(65);
    set("gender", "male");
    set("age", 65);
    set("long",
        "魚鐵山是雪吟莊的莊主，也是當今武林號稱「六賢」之一的武林高手，魚鐵山\n"
        "成名已近四十年，和當今武林盟主於蘭兼毅是總角之交，曾一起在天邪派前掌\n"
        "門於蘭焱門下學藝，不過由於於蘭兼毅是天邪國公世子，因此於蘭焱收於蘭兼\n"
        "毅為師弟，而魚鐵山反而要稱這位小他三歲的老友師叔了。\n");
    set("custom_faction", "fighter.snow");   // 雪吟莊（docs/martial_arts/門派武功對照表.md）
    set_power("S");
    setup();
    carry_object("/custom/armor/head/brass_hat")->wear();   // 黃呢鐵帽
    carry_object("/custom/armor/waist/water_dragon_girdle")->wear();   // 蛟龍帶
    carry_object("/custom/armor/feet/spider_boots")->wear();   // 玄蛛皂白靴
    carry_object("/custom/armor/cloth/golden_robe")->wear();   // 金絲長袍
    carry_object("/custom/armor/finger/ring_of_mighty_dragon")->wear();   // 巨龍指環
    carry_object("/custom/weapon/blade/golden_blade")->wield();   // 金絲八卦刀
}
