// /custom/legacy_npc/barbarian_chief.c — 舊站 NPC：野人酋長（Barbarian chief）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：獸皮裙(Fur sarong)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("野人酋長", ({ "barbarian chief", "barbarian", "chief" }));
    set_race("human");
    set_class("fighter");
    set_level(5);
    set("gender", "male");
    set("age", 45);
    set("long",
        "一個赤身露體的野人﹐正張大了嘴對著你疵牙裂嘴。\n");
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("C");
    setup();
    carry_object("/custom/weapon/staff/bone_staff")->wield();   // 白骨杖
}
