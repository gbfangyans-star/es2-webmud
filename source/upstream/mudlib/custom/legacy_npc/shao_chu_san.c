// /custom/legacy_npc/shao_chu_san.c — 舊站 NPC：蕭秋山（Shao chu-san）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黑風寨；房間：武器室。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("蕭秋山", ({ "shao chu-san", "shao", "chu-san" }));
    set("title", "武術教頭");
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一個相貌相當俊秀的年青人, 山寨中習武的各個環節都必須經過他的\n"
        "同意, 若未經許可偷學習武功, 通常命運是相當悲慘的, 他同時也是\n"
        "黑風寨中高手之一, 所以整個山寨的人也都很怕他。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("B");
    setup();
    carry_object("/custom/weapon/sword/hero_sword")->wield();   // 英雄劍
    carry_object("/custom/armor/armor/iron_armor")->wear();   // 鐵戰甲
}
