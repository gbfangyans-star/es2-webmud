// /custom/legacy_npc/dong_fang_gu_ming.c — 舊站 NPC：東方孤冥（Dong-fang gu ming）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：素雲頭巾(Cloud-circlet)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("東方孤冥", ({ "dong-fang gu ming", "dong-fang", "ming" }));
    set("title", "玄天教主");
    set_race("human");
    set_class("scholar");
    set_level(65);
    set("gender", "male");
    set("age", 75);
    set("long",
        "喜好習武﹐年輕時遊走江湖結識各派高手﹐雖然有家傳心法護身﹐卻苦於僅靠家\n"
        "傳劍法難以立足江湖。三十四歲那年﹐他巧得半頁陰心太妃﹐在幾位朋友的解說\n"
        "和指點下創出一套怪異的劍訣配合家傳的玄天劍法頗具威力。數年後﹐他聯絡當\n"
        "初幫他解說陰心太妃的朋友們創立玄天教。\n");
    set("custom_faction", "scholar.sky");   // 玄天派（docs/martial_arts/門派武功對照表.md）
    set_power("S");
    setup();
    carry_object("/custom/armor/waist/white_jade_girth")->wear();   // 流雲清玉帶
    carry_object("/custom/armor/cloth/white_scholar_dress")->wear();   // 白色長衫
    carry_object("/custom/armor/finger/han_jade_ring")->wear();   // 漢玉戒指
    carry_object("/custom/weapon/sword/silver_sword")->wield();   // 洗銀劍
}
