// /custom/legacy_npc/evil_spirit_of_storm.c — 舊站 NPC：墮落的風神（Evil spirit of storm）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：京畿、平陽山、神域；房間：後海湖、s路、迷霧中。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("墮落的風神", ({ "evil spirit of storm", "evil", "storm" }));
    set_race("avatar");
    set_class("taoist");
    set_level(70);
    set("gender", "female");
    set("age", 7865);
    set("long",
        "墮落的風神看起來沒有什麼特別。\n");
    set("custom_faction", "taoist.storm");   // 玄衣派（docs/martial_arts/門派武功對照表.md）
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
        (: command, "cast 4" :)
    }));
    set_power("S");
    setup();
    carry_object("/custom/weapon/sword/storm_lords_feather")->wield();   // 風神之羽
}
