// /custom/legacy_npc/ou_yan_wu_ji_2.c — 舊站 NPC：歐陽無極（Ou-yan wu ji）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：茅山、康平村；房間：小客店。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("歐陽無極", ({ "ou-yan wu ji", "ou-yan", "ji" }));
    set("title", "隱風觀觀主");
    set_race("human");
    set_class("taoist");
    set_level(40);
    set("gender", "male");
    set("age", 45);
    set("long",
        "隱風觀觀主本是四十多年前離開茅山﹐自創隱風觀的宇文太極。怎料數日前\n"
        "宇文太極竟忽然一命歸天﹐引得江湖中盛傳『茅山劍法』再顯與世。新任的\n"
        "隱風觀觀主﹐歐陽無極則是一口咬定宇文太極是忙於重建茅山﹐操勞過度而\n"
        "死。歐陽無極是宇文太極生前最鐘愛的弟子﹐而且在『茅山幻術』上的造詣\n"
        "頗深。他此時離開隱風觀據說是有事要和靈雲觀觀主和幻霧觀觀主商討。\n");
    set_power("A");
    setup();
    carry_object("/custom/armor/cloth/green_robe")->wear();   // 青衣道袍
    carry_object("/custom/weapon/sword/peachwood_sword")->wield();   // 桃木劍
}
