// /custom/legacy_npc/ro_yi.c — 舊站 NPC：駱易（Ro yi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：步玄派；房間：—。
門派「步玄派」尚未列入門派武功對照表，先不設門派記號。
尚未製作的裝備（先空著）：逐風刃(Windfury sword)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("駱易", ({ "ro yi", "ro", "yi" }));
    set("title", "步玄派掌門");
    set_race("human");
    set_class("scholar");
    set_level(65);
    set("gender", "male");
    set("age", 55);
    set("long",
        "駱易本人性格恬淡，雖然身為步玄派掌門人，卻極為謙退自抑，外人只知道駱易\n"
        "少年時曾孤身一人犯險闖入西方大漠的飛狼城，救回當今的皇帝及香雪王，成為\n"
        "轟動一時的人物。駱易辭卻了朝廷及香雪王的豐厚賞賜及高官厚祿，隱居在喬陰\n"
        "的祖宅，也成為江湖傳頌的美談。\n");
    set_power("S");
    setup();
    carry_object("/custom/armor/armor/black_harness")->wear();   // 玄晦戰甲
    carry_object("/custom/armor/finger/han_jade_ring")->wear();   // 漢玉戒指
    carry_object("/custom/armor/feet/snakeskin_boots")->wear();   // 青蟒靴
    carry_object("/custom/armor/waist/white_jade_girth")->wear();   // 流雲清玉帶
    carry_object("/custom/armor/cloth/golden_robe")->wear();   // 金絲長袍
    carry_object("/custom/armor/head/headgear")->wear();   // 紫紗逍遙巾
    carry_object("/custom/weapon/sword/cloudslay_sword")->wield();   // 落雲刃
}
