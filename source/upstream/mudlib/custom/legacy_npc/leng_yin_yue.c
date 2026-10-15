// /custom/legacy_npc/leng_yin_yue.c — 舊站 NPC：冷吟月（Leng yin yue）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：冷府；房間：閨房、密室。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("冷吟月", ({ "leng yin yue", "leng", "yue" }));
    set("title", "冷府千金");
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "female");
    set("age", 15);
    set("long",
        "在你眼前的是一位窈窕的清秀佳人，她瓜子般的精緻臉龐略顯蒼白，黑\n"
        "白分明的雙眸難掩驚慌的神情。\n");
    set_power("C");
    setup();
}
