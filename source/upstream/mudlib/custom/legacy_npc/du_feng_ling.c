// /custom/legacy_npc/du_feng_ling.c — 舊站 NPC：杜風凌（Du feng ling）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山、龍安鎮；房間：客棧。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("杜風凌", ({ "du feng ling", "du", "ling" }));
    set("title", "幻霧觀觀主");
    set_race("malik");
    set_class("taoist");
    set_level(40);
    set("gender", "male");
    set("age", 75);
    set("long",
        "杜風凌本是西方大漠的巫首族人﹐自幼拜林遠為師﹐修習茅山道法。也許是\n"
        "因為天賦異常﹐入門十數年就熟練的掌握了茅山道法的精髓並將其融會貫通,\n"
        "漸漸將一些不受重視的小把戲發展起來﹐當時盛傳杜風凌將會是下任茅山的\n"
        "掌門人。怎料當時的茅山掌門人﹐林遠﹐為了追查茅山劍法竟然屍橫荒野﹐\n"
        "一時間茅山派一片大亂。不少人因鄙視杜風凌所擅長的『茅山奇術』竟然離\n"
        "開茅山自成流派﹐而杜風凌也因其家族牽扯到黃泉村一事﹐而不得不暫回西\n"
        "方大漠。當他返回天朝以後﹐無法說服他的師兄弟重歸茅山﹐便憤然再返大\n"
        "漠﹐借助他家族在大漠的勢力自創『幻霧觀』。此次不知是為何事﹐竟然又\n"
        "來到天朝境內。\n");
    set_power("A");
    setup();
    carry_object("/custom/armor/cloth/green_robe")->wear();   // 青衣道袍
    carry_object("/custom/weapon/sword/peachwood_sword")->wield();   // 桃木劍
    carry_object("/custom/armor/finger/han_jade_ring")->wear();   // 漢玉戒指
}
