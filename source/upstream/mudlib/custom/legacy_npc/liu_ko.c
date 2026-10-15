// /custom/legacy_npc/liu_ko.c — 舊站 NPC：劉可（Liu ko）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：哭笑門；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("劉可", ({ "liu ko", "liu", "ko" }));
    set_race("yenhold");
    set_class("commoner");
    set_level(1);
    set("gender", "male");
    set("age", 45);
    set("long",
        "你面前的這個中年男子只是哭笑門的一個管事，奉命將這裡改造成一間倉庫。\n"
        "他身後鼓鼓囊囊的袋子里也許有什麼好東西也不一定。你可以用 list 列出可\n"
        "以買哪些裝備﹐用 buy 跟他買。\n");
    set_power("C");
    setup();
}
