// /custom/legacy_npc/wu_dauton.c — 舊站 NPC：武道通（Wu dauton）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：武陀灸堂；房間：武陀灸堂。
門派「五陀灸堂」尚未列入門派武功對照表，先不設門派記號。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("武道通", ({ "wu dauton", "wu", "dauton" }));
    set("title", "武陀灸堂堂主");
    set("nickname", "鬼華陀");
    set_race("human");
    set_class("alchemist");
    set_level(60);
    set("gender", "male");
    set("age", 75);
    set("long",
        "武道通年輕時本為龍圖丹派的方士, 因為一次因緣際會結識了一位江湖異人, 習得\n"
        "了幾手針灸之術, 從此便不再苦煉丹道, 開始如著魔般浸淫於施針下灸之學。之後\n"
        "竟因久疏龍圖丹派本門功夫, 而遭致開革之禍。武道通離開龍圖丹派之後, 便隱居\n"
        "於斐縣縣郊, 為當地居民針灸治病, 沒有想到卻聲名大噪起來, 由於醫術高明, 行\n"
        "事瘋癲乖張, 得了個「鬼華陀」的稱號。到了晚年, 乃自行開宗立派, 創設「武陀\n"
        "灸堂」, 傳授附近居民武藝與防身灸術, 門下弟子不下百人, 多雲遊四海, 行醫救\n"
        "世。\n");
    set_power("S");
    setup();
    carry_object("/custom/armor/feet/boots_of_cleanse")->wear();   // 塵不沾
    carry_object("/custom/weapon/needle/bee_needle")->wield();   // 蜂尾針
    carry_object("/custom/armor/finger/tiger_ring")->wear();   // 虎紋戒指
    carry_object("/custom/weapon/needle/needle_of_bone_maggot");   // 附骨之蛆
}
