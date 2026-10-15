// /custom/legacy_npc/old_taoist.c — 舊站 NPC：安懶道人（Old taoist）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：天邪國；房間：草廬。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("安懶道人", ({ "old taoist", "old", "taoist" }));
    set_race("human");
    set_class("taoist");
    set_level(60);
    set("gender", "male");
    set("age", 85);
    set("long",
        "安懶道人是個鬍鬚花白的老道士，他曾經在天邪國擔任御史大夫達三十多\n"
        "年，後來辭官入山學道。\n");
    set("custom_faction", "taoist.storm");   // 玄衣派（docs/martial_arts/門派武功對照表.md）
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
        (: command, "cast 4" :)
    }));
    set_power("A");
    setup();
    carry_object("/custom/armor/finger/sapphire_ring")->wear();   // 藍水晶戒指
    carry_object("/custom/armor/cloth/tao_robe")->wear();   // 杏黃道袍
    carry_object("/custom/armor/armor/magic_armor")->wear();   // 法胄
    carry_object("/custom/weapon/sword/sword_of_raven")->wield();   // 黃雀寶劍
    carry_object("/custom/weapon/sword/peachwood_sword");   // 桃木劍
}
