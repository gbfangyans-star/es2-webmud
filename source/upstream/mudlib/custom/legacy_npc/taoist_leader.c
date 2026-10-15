// /custom/legacy_npc/taoist_leader.c — 舊站 NPC：白齊（Taoist leader）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：太乙觀；房間：賓客宿房。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("白齊", ({ "taoist leader", "taoist", "leader" }));
    set("title", "太乙觀觀主");
    set_race("human");
    set_class("taoist");
    set_level(50);
    set("gender", "male");
    set("age", 75);
    set("long",
        "在你眼前的是一位仙風道骨的道士，身著一件淡青色道袍，渾身\n"
        "散發出一股悠然的風範與氣度，他就是太乙觀的觀主--白齊。太\n"
        "乙觀內的上清道長，玉清道長跟玄清道長都是他的得意門徒，他\n"
        "對待觀內的小道童，道士們也都很親切，可以說是太乙觀中最具\n"
        "有影響力的人物。\n");
    set("custom_faction", "taoist.freeze");   // 素衣派（docs/martial_arts/門派武功對照表.md）
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
        (: command, "cast 4" :)
    }));
    set_power("A");
    setup();
    carry_object("/custom/weapon/sword/shome_sword")->wield();   // 少眉劍
    carry_object("/custom/armor/feet/black_cloth_boots")->wear();   // 黑布鞋
    carry_object("/custom/armor/cloth/green_robe")->wear();   // 青衣道袍
}
