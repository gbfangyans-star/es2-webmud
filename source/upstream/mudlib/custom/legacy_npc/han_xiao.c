// /custom/legacy_npc/han_xiao.c — 舊站 NPC：韓笑（Han xiao）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：虎刀門；房間：—。
尚未製作的裝備（先空著）：虎紋斬馬刀(Reckless blade)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("韓笑", ({ "han xiao", "han", "xiao" }));
    set("title", "虎刀門掌門");
    set_race("human");
    set_class("fighter");
    set_level(60);
    set("gender", "female");
    set("age", 35);
    set("long",
        "韓笑自幼極具習武天賦而且練功也很勤，所以在二十多歲時就已是名震武\n"
        "林的好手。虎刀門前掌門去世時不顧眾人反對，毅然將掌門之位傳給了當\n"
        "時只有二十八歲的韓笑，此事在武林之上也引起不小的震動。如今韓笑的\n"
        "內功刀法比起六年前更為精純，成為武林之中公認的最年輕的武學大師。\n");
    set("custom_faction", "fighter.tiger");   // 虎刀門（docs/martial_arts/門派武功對照表.md）
    set_power("S");
    setup();
    carry_object("/custom/armor/feet/embroidery_boots")->wear();   // 繡花鞋
    carry_object("/custom/armor/waist/girl_girth")->wear();   // 束腰帶
    carry_object("/custom/armor/finger/bloodjade_ring")->wear();   // 血玉戒指
    carry_object("/custom/armor/armor/white_dragon_plate")->wear();   // 混天白龍
    carry_object("/custom/armor/cloth/tigerish_robe")->wear();   // 虎皮長袍
    carry_object("/custom/armor/neck/tiger_necklace")->wear();   // 虎牙項鏈
}
