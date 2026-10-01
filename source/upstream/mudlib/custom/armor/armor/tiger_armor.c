/* 破蠡虎皮 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("破蠡虎皮", ({ "tiger armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "張");
        set("value", 91000);
        set("long",
            "這是從神獸破蠡身上撕下來的一張虎皮, 它散發出的濃厚血腥味令你感到有\n"
            "些興奮...\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "str": 1,
            "armor": 30,
            "cor": 1,
        ]));
    }
    setup();
}
