// /custom/legacy_npc/yan_she.c — 舊站 NPC：言歙（Yan she）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：漕幫；房間：縣衙客房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("言歙", ({ "yan she", "yan", "she" }));
    set("title", "御史大夫");
    set_race("yaksa");
    set_class("commoner");
    set_level(20);
    set("gender", "male");
    set("age", 55);
    set("long",
        "言歙乃是當今朝中紅人，不到不惑之年已官拜御史大夫，這次似乎是為\n"
        "了漕幫之事而來，漕幫行事向來低調，朝廷忽然對之展開調查想來必有\n"
        "原因。其為人貪杯好酒，但是辦起事來卻又十分穩當，武功平平不過逃\n"
        "命功夫一流。\n");
    set_power("B");
    setup();
    carry_object("/custom/armor/head/jade_hat")->wear();   // 綠玉頂戴
    carry_object("/custom/armor/cloth/dragon_cloth")->wear();   // 蟠龍朝服
}
