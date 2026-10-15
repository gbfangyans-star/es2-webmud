// /custom/legacy_npc/red_lady.c — 舊站 NPC：紅衣女子（Red lady）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：短獵刀(Tanto)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("紅衣女子", ({ "red lady", "red", "lady" }));
    set_race("human");
    set_class("fighter");
    set_level(40);
    set("gender", "female");
    set("age", 35);
    set("long",
        "一個身形婀娜的中年女子, 她豔美的臉龐和那如羊脂白玉般的肌膚, 不\n"
        "禁令你看傻了眼。她一臉茫然地看著你, 口中喃喃地唱著清淒的小調,\n"
        "你見到她的雙手染滿了血跡, 在她雪白的手臂上如一片片滿開的鮮紅牡\n"
        "丹 ...。\n");
    set_power("A");
    setup();
    carry_object("/custom/armor/armor/white_dragon_plate")->wear();   // 混天白龍
    carry_object("/custom/weapon/sword/iron_sword")->wield();   // 青鋼短劍
}
