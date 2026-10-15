// /custom/legacy_npc/yu_lan_jian_yi.c — 舊站 NPC：於蘭兼毅（Yu lan jian yi）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：天邪國；房間：—。
門派「天邪派」尚未列入門派武功對照表，先不設門派記號。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("於蘭兼毅", ({ "yu lan jian yi", "yu", "yi" }));
    set("title", "天邪派掌門");
    set("nickname", "武林盟主");
    set_race("human");
    set_class("fighter");
    set_level(70);
    set("gender", "male");
    set("age", 55);
    set("long",
        "於蘭兼毅是當今的武林盟主﹐也是天邪國公獨生子﹐如果你以為他是\n"
        "靠著貴族的身分而獲得武林盟主的地位﹐你可是會大吃一驚的﹐天邪\n"
        "國一向是於蘭宗室掌管武術之秘的一支﹐宗室中的人物在武林之中向\n"
        "來依照武林規矩﹐於蘭兼毅在武林中成名已超過三十年﹐除了執掌天\n"
        "邪派門戶之外﹐也和武林中另外五位奇人合稱「六賢」。\n");
    set_power("S");
    setup();
    carry_object("/custom/armor/head/brass_hat")->wear();   // 黃呢鐵帽
    carry_object("/custom/armor/feet/spider_boots")->wear();   // 玄蛛皂白靴
    carry_object("/custom/armor/armor/dragon_armor")->wear();   // 怒龍錦冑
    carry_object("/custom/armor/hand/skin_gloves")->wear();   // 鹿皮手套
}
