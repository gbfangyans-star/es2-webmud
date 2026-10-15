// /custom/legacy_npc/liuh_don_lu.c — 舊站 NPC：柳東蘆（Liuh don-lu）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("柳東蘆", ({ "liuh don-lu", "liuh", "don-lu" }));
    set("title", "封山派掌門");
    set_race("human");
    set_class("fighter");
    set_level(70);
    set("gender", "male");
    set("age", 55);
    set("long",
        "柳東蘆是赫赫有名的封山劍派掌門人，封山劍派原本只以劍法見長，但是柳東\n"
        "蘆近幾年以家傳拳法融合封山劍法劍意，彌補了封山劍法中的許多缺點，四年\n"
        "前的武林大會便技壓群雄奪得武林盟主的寶座，但是他當武林盟主不到半年便\n"
        "宣佈退隱，據說是因為身染絕症之故，不過在你面前的這位年約五、六十歲的\n"
        "白髮老者似乎仍然精神矍鑠，不像是身有重病的樣子。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("S");
    setup();
    carry_object("/custom/armor/leg/red_scale_leggings")->wear();   // 火鱗脛甲
    carry_object("/custom/armor/waist/red_scale_girth")->wear();   // 火鱗腰帶
    carry_object("/custom/armor/hand/red_scale_gloves")->wear();   // 火鱗手套
    carry_object("/custom/armor/head/red_scale_helm")->wear();   // 火鱗盔
    carry_object("/custom/armor/feet/red_scale_boots")->wear();   // 火鱗靴
    carry_object("/custom/armor/armor/red_scale_plate")->wear();   // 火鱗胸鎧
    carry_object("/custom/armor/cloth/red_scale_cloth")->wear();   // 火鱗衣
    carry_object("/custom/weapon/sword/blackthorn")->wield();   // 玄蘇劍
}
