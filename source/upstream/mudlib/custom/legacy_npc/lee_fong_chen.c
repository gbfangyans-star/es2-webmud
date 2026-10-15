// /custom/legacy_npc/lee_fong_chen.c — 舊站 NPC：李瘋塵（Lee fong chen）。
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
    set_name("李瘋塵", ({ "lee fong chen", "lee", "chen" }));
    set("nickname", "蟬翼刀");
    set_race("ashura");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "李瘋塵看起來相當強壯，一身黑色裝扮，腰上繫著一把長約三尺，形\n"
        "狀類似蟬翼的刀刃。也許他就是十年前江湖中那位殺人不眨眼的蟬翼\n"
        "刀客。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("B");
    setup();
    carry_object("/custom/weapon/blade/wing_blade")->wield();   // 蟬翼刀
    carry_object("/custom/armor/armor/raw_iron_armor")->wear();   // 生鐵戰甲
    carry_object("/custom/armor/finger/beast_ring")->wear();   // 獸面玉戒
    carry_object("/custom/armor/hand/black_gauntlets")->wear();   // 黑鐵護手
}
