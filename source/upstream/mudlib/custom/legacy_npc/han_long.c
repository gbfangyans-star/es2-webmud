// /custom/legacy_npc/han_long.c — 舊站 NPC：韓龍（Han long）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：白虎堂；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("韓龍", ({ "han long", "han", "long" }));
    set("title", "虎刀門知事");
    set_race("yaksa");
    set_class("fighter");
    set_level(30);
    set("gender", "male");
    set("age", 45);
    set("long",
        "韓龍四十二歲當上白虎堂知事，掌管各種情報的蒐集與分析。他\n"
        "也建立了一個龐大的情報網，把江湖中人每天所有大小事通通納\n"
        "入白虎堂的蒐集範圍。讓許多有意為惡的門派不敢輕舉妄動。\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/axe/axe_of_bloodmoon")->wield();   // 血月斧
    carry_object("/custom/armor/head/jade_hat")->wear();   // 綠玉頂戴
    carry_object("/custom/armor/cloth/dragon_cloth")->wear();   // 蟠龍朝服
}
