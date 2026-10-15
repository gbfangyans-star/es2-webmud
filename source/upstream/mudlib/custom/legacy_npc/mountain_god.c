// /custom/legacy_npc/mountain_god.c — 舊站 NPC：桃仙（Mountain god）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：天山；房間：桃花林、桃園。
尚未製作的裝備（先空著）：天山野蔘鬚(Senxu)、【脈穴內經】(Book of anatomy)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("桃仙", ({ "mountain god", "mountain", "god" }));
    set_race("avatar");
    set_class("taoist");
    set_level(30);
    set("gender", "male");
    set("age", 1405);
    set("long",
        "桃仙看起來沒有什麼特別。\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/staff/zenstaff")->wield();   // 禪杖
}
