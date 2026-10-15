// /custom/legacy_npc/liuh_hui_xin.c — 舊站 NPC：柳繪心（Liuh hui xin）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：—。
尚未製作的裝備（先空著）：絲綢女衫(Silk dress)。
*/
inherit "/custom/legacy_npc/legacy_npc";

void create()
{
    seteuid(getuid());
    set_name("柳繪心", ({ "liuh hui xin", "liuh", "xin" }));
    set("title", "封山派弟子");
    set_race("human");
    set_class("fighter");
    set_level(20);
    set("gender", "female");
    set("age", 15);
    set("long",
        "一個十二、三歲的小女孩，臉上稚氣未脫，卻在眉目之間顯露出一股頤氣指使\n"
        "的威嚴。\n");
    set("custom_faction", "fighter.fonxan");   // 封山派（docs/martial_arts/門派武功對照表.md）
    set_power("B");
    setup();
    carry_object("/obj/area/obj/longsword")->wield();   // 長劍
}
