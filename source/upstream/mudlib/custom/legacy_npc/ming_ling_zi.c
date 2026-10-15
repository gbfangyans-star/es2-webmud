// /custom/legacy_npc/ming_ling_zi.c — 舊站 NPC：螟蛉子（Ming ling zi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：古墓場；房間：內房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("螟蛉子", ({ "ming ling zi", "ming", "zi" }));
    set_race("malik");
    set_class("taoist");
    set_level(20);
    set("gender", "male");
    set("age", 85);
    set("long",
        "螟蛉子是跟杜風凌從西方大漠來的一位道士，平生以探求神秘的地方為樂。\n"
        "據說，他有辦法到達三個不屬於人間的地方：古墓場、夜神殿和蟠龍殿。他\n"
        "這次來天朝多半是為了幫杜風凌的幻霧觀在江湖中贏得一席之地吧。\n");
    set_power("A");
    setup();
}
