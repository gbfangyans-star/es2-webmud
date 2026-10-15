// /custom/legacy_npc/white_hell_agent.c — 舊站 NPC：白無常（White hell agent）。
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
    set_name("白無常", ({ "white hell agent", "white", "agent" }));
    set("title", "勾魂使者");
    set_race("malik");
    set_class("taoist");
    set_level(50);
    set("gender", "male");
    set("age", 5325);
    set("long",
        "勾魂使者白無常是負責將因戰亂和意外而喪生的人的靈魂引去接受\n"
        "閻王的審判。一般來說，活人是見不到他的。而現在他就在你的面\n"
        "前，而且滿臉愁容，似乎遇到了甚麼麻煩。\n");
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
}
