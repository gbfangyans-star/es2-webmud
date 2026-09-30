/* 旋芒戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("旋芒戒", ({ "sparkling ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 6000);
        set("long",
            "相傳數十年前, 嵐城仙物旋芒戒重現於世, 此物具神奇靈性, 輔人斬妖伏魔之\n"
            "神力, 而後卻搌轉被太湖雙惡所奪, 並於太湖與攬天門主死鬥時逸失.\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 1,
            "taoism-freeze": 5,
            "taoism-fire": 5,
        ]));
    }
    setup();
}
