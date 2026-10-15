// /custom/legacy_npc/yan_kuang_phon.c — 舊站 NPC：閰狂風（Yan kuang phon）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：黑風寨；房間：黑風寨大廳。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("閰狂風", ({ "yan kuang phon", "yan", "phon" }));
    set("title", "黑風寨四頭目");
    set_race("yaksa");
    set_class("fighter");
    set_level(40);
    set("gender", "male");
    set("age", 75);
    set("long",
        "閰狂風乃是黑風寨的四頭目, 早年拜於封山門下, 但不滿其於\n"
        "封山派之內不受到重視與重用, 故而積怨心中, 也因此他的封山\n"
        "劍招夾帶著一股邪惡之氣, 在幾十年前的一場封山派所舉行的武\n"
        "功比試大會中, 由於出手毫不留情, 殺死其同門師兄, 而因此被\n"
        "逐出師門, 但因為其天資聰穎早已習得封山武功精髓, 加上長年\n"
        "自行修練, 已經到了爐火純青的地步。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set("legacy_aggressive", 1);   // 看到玩家就下殺手
    set_power("B");
    setup();
    carry_object("/custom/weapon/sword/smashing_sword")->wield();   // 巨劍『破石』
    carry_object("/custom/armor/armor/armor_of_violet_rohan")->wear();   // 紫羅點翠戰甲
    carry_object("/custom/armor/cloth/sky_earth_cloth")->wear();   // 天地雲衫
}
