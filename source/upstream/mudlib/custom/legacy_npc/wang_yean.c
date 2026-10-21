// /custom/legacy_npc/wang_yean.c — 舊站 NPC：王燕（Wang yean）。
/*
LEGACY NPC. 名稱、英文 ID、敘述、年紀、性別、種族、裝備取自舊站畫面紀錄（DOCUMENTED，
docs/LEGACY_ROOM_NPC_COMPENDIUM.md）；職業、等級、強度、門派、行為依使用者提供的
「舊有 NPC 待製作清單」（2026-10-15）。尚未放入地圖。
舊站區域：未能判定；房間：瓦屋。
*/
inherit "/custom/legacy_npc/legacy_npc";
inherit "/feature/npc/vendor";   // F_VENDOR（npc.h 會重複繼承 NPC，所以直接寫路徑）

// 販賣肥遺骨粉與松材（使用者定案，2026-10-21）。
void init()
{
    legacy_npc::init();
    add_action("do_vendor_list", "list");
}

void create()
{
    seteuid(getuid());
    set_name("王燕", ({ "wang yean", "wang", "yean" }));
    set("nickname", "花中菩提");
    set_race("human");
    set_class("alchemist");
    set_level(20);
    set("gender", "female");
    set("age", 35);
    set("long",
        "一個滿身藥味, 神情專注的女子正在清理一些木材, 似乎沒有注意到你正在看\n"
        "她. 有她的裝束來看, 不像學武之人, 反到像是到處尋藥之神醫. 她師兄陳度\n"
        "好管閒事, 反倒在藥材的研究上, 比不上默默鑽研的王燕. 由其專注的神貌,\n"
        "似乎正在調理重要的配方.\n");
    set("merchandise", ([
        "/obj/food/snake_powder" : 100,              // 肥遺骨粉
        "/obj/alchemist/heat_firewood" : 5000,       // 松材
    ]));
    set_power("B");
    setup();
    carry_object("/custom/weapon/dagger/shennong_dagger")->wield();   // 神農匕
    carry_object("/custom/armor/head/goat_hat")->wear();   // 神羊帽
    carry_object("/obj/cloth")->wear();   // 布衣
}
