// /custom/legacy_npc/liu_kei.c — 舊站 NPC：劉開（Liu kei）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：檒城；房間：街道。
尚未製作的裝備（先空著）：皮甲(Leather armor)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("劉開", ({ "liu kei", "liu", "kei" }));
    set("title", "檒城衛兵統領");
    set_race("human");
    set_class("soldier");
    set_level(30);
    set("gender", "male");
    set("age", 35);
    set("long",
        "劉開是檒城衛兵統領, 生性忌惡如仇, 他層經捉拿過無數的壞人,也立\n"
        "下過不少的戰功.\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/pike/solar_pike")->wield();   // 射日長槍
}
