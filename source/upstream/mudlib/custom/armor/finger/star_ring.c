/* 星光指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m星光指環\x1b[m", ({ "star ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 150000);
        set("long",
            "\x1b[1;37m月神「銀蟾」\x1b[m下凡人間遊覽時偶遇一少女，愛其清純羞澀便要來少女\n"
            "一縷秀髮點綴夜幕。數年後，\x1b[1;37m月神「銀蟾」\x1b[m重回人間，見這少女已有\n"
            "情郎，便取來造星之石化成戒指送給少女，祝福她一生平安幸福。\n"
            "相傳只要將四神的印記鑲於其上，即可重塑一個人在某項技能的天賦。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": 50,
            "awarness": 100,
            "armor_vs_wind": 100,
            "armor_vs_lightning": 200,
        ]));
    }
    setup();
}
