// /custom/legacy_npc/zhang_yun.c — 舊站 NPC：張雲（Zhang yun）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：虎刀門；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("張雲", ({ "zhang yun", "zhang", "yun" }));
    set("title", "虎刀門護衛");
    set_race("human");
    set_class("fighter");
    set_level(35);
    set("gender", "male");
    set("age", 35);
    set("long",
        "張雲十幾年前便拜在虎刀門耆宿「高慎」門下習武，後來到總壇參加比武\n"
        "大會，苦鬥近百合險勝「屠龍虎」駱雲飛，不料卻在十合之內敗給虎刀掌\n"
        "門僅十三歲的義女「孫漪」。此後他便留在總壇勤奮練功，五年不曾下山。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/custom/armor/armor/hell_dragon_armor")->wear();   // 冥龍甲
    carry_object("/custom/armor/cloth/tiger_coat")->wear();   // 斑斕虎氅
    carry_object("/custom/armor/head/war_hat")->wear();   // 戰帽
    carry_object("/custom/weapon/blade/colosus_blade")->wield();   // 巨刀
}
