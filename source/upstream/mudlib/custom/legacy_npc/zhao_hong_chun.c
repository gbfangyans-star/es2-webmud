// /custom/legacy_npc/zhao_hong_chun.c — 舊站 NPC：趙弘春（Zhao hong chun）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：紫煙鎮；房間：—。
尚未製作的裝備（先空著）：長袍馬掛(Robe)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("趙弘春", ({ "zhao hong chun", "zhao", "chun" }));
    set("title", "縣令");
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("gender", "male");
    set("age", 75);
    set("long",
        "趙弘春是酉縣的縣令, 不過謠傳說他的官位是花銀子買來的, 再加上\n"
        "他平時總是常常結交一些達官貴人, 因此在仕途上也是一帆風順, 不\n"
        "過紫煙鎮的居民卻普遍對這位縣令沒有好感, 據說雲鶴山的盜匪就是\n"
        "因為和他作對, 而被官府通緝, 被迫躲進雲鶴山據地為王, 也因此趙\n"
        "弘春處心積慮的想要消滅那群盜匪, 以除其心腹大患.\n");
    set_power("C");
    setup();
}
