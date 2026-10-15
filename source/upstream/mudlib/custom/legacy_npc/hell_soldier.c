// /custom/legacy_npc/hell_soldier.c — 舊站 NPC：地府鬼卒（Hell soldier）。
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
    set_name("地府鬼卒", ({ "hell soldier", "hell", "soldier" }));
    set_race("human");
    set_class("soldier");
    set_level(25);
    set("gender", "male");
    set("age", 15);
    set("long",
        "一個青面獠牙的鬼卒﹐雙眼大如銅鈴﹐身上穿著有如陽間官兵的衣服。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/armor/iron_torso")->wear();   // 鑌鐵胸鎧
    carry_object("/custom/weapon/pike/iron_fork")->wield();   // 鑌鐵叉
}
