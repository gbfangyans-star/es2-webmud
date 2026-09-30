/* 渾鐵龍蛇槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("渾鐵龍蛇槍", ({ "iron pike", "pike" }));
    set_weight(15700);
    init_damage(5, 10, 100, 4, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一枝長約八尺的鐵鑄長槍，看起來相當的沉重，這枝槍乃是天朝猛將\n"
            "黃靖國揚名沙場的利器，黃靖國精於槍術，使動此槍之際有如靈蛇矯\n"
            "龍般令人捉摸不定，實有神鬼莫測之威，龍蛇槍之名因而遠揚。\n");
    }
    setup();
}
