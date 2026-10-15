// /custom/legacy_npc/jia_qiu_yu.c — 舊站 NPC：賈秋雨（Jia qiu yu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：軟綢長袍(Silk robe)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("賈秋雨", ({ "jia qiu yu", "jia", "yu" }));
    set_race("human");
    set_class("fighter");
    set_level(10);
    set("gender", "male");
    set("age", 15);
    set("long",
        "他是一位方臉大耳﹐濃眉高顴的俊挺少年﹐年紀大約十七八歲﹐一身白\n"
        "綃般的素淨長袍衣帶飛揚﹐背懸六尺長劍﹐腰繫翡翠白玉佩﹐風度翩翩\n"
        "﹐有如玉樹臨風。\n");
    set_power("C");
    setup();
    carry_object("/obj/area/obj/longsword")->wield();   // 長劍
}
