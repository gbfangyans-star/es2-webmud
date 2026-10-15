// /custom/legacy_npc/zhong_hao.c — 舊站 NPC：鍾豪（Zhong hao）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：碧幽部落；房間：鍾豪房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("鍾豪", ({ "zhong hao", "zhong", "hao" }));
    set_race("dingling");
    set_class("fighter");
    set_level(10);
    set("gender", "male");
    set("age", 55);
    set("long",
        "碧幽部落的族長，他不久前到森林裡去一趟回來就得了一場大病，不但到現在\n"
        "都還沒好，還越來越嚴重，他已經派人去找醫生來看病，也吃過多種草藥，都\n"
        "還是沒有好轉的跡象。\n");
    set_power("B");
    setup();
}
