// /custom/legacy_npc/cheng_huai.c — 舊站 NPC：程槐（Cheng huai）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：粗麻布衣(Cloth)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("程槐", ({ "cheng huai", "cheng", "huai" }));
    set_race("human");
    set_class("fighter");
    set_level(25);
    set("gender", "male");
    set("age", 35);
    set("long",
        "程槐看起來非常強壯, 他雙手上長滿了因長期握斧而長的厚繭, 背上還背著一\n"
        "柄重斧, 據說他年輕時曾經以一把利斧「驂龍翔」挑了一個山寨的土匪, 讓道\n"
        "上盜匪都聞之喪膽, 不過看他現在臉色不太好, 好像是身上受了重傷。\n");
    set_power("B");
    setup();
    carry_object("/custom/weapon/axe/wyvern_axe")->wield();   // 驂龍翔
}
