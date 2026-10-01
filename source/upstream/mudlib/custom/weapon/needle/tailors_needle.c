/* 繡花銀針 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("繡花銀針", ({ "tailor's needle", "needle" }));
    set_weight(500);
    init_damage(3, 15, 100, 10, "needle");

    if( !clonep() ) {
        set("wield_as", "needle");
        set("unit", "支");
        set("value", 35000);
        set("long",
            "一支雪白的細長銀針，針上淺淺的刻有一些花草的圖案。\n");
        set("apply_weapon/needle", ([
            "wittiness": 30,
            "attack": 30,
        ]));
    }
    setup();
}
