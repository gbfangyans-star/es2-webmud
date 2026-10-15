// /custom/legacy_npc/guard_of_hell.c — 舊站 NPC：土伯（Guard of hell）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山；房間：茅山石陣。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("土伯", ({ "guard of hell", "guard", "hell" }));
    set_race("headless");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 15);
    set("long",
        "身高三十丈的黑色巨人﹐頭生雙角﹐腹成牛腹狀。相傳﹐土伯是幽都的\n"
        "守門者﹐終日驅趕百鬼﹐性情殘暴。\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/whip/war_whip")->wield();   // 戰鞭
}
