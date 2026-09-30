/* 赤血槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("赤血槍", ({ "blood pike", "pike" }));
    set_weight(15700);
    init_damage(5, 10, 100, 4, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一枝長約八尺的鐵槍，看起來頗為沉重，乃是天朝良匠專為各軍營\n"
            "猛將鑄造的兵器。\n");
    }
    setup();
}
