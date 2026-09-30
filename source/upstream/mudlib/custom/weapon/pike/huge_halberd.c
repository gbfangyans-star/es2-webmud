/* 方天畫戟 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;37m方天畫戟\x1b[m", ({ "huge halberd", "pike" }));
    set_weight(20000);
    init_damage(5, 13, 100, 10, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一枝一丈多長的大戟﹐自古以來長戟便是戰場上最具殺傷力的長\n"
            "兵器﹐結合了長槍的攻擊範圍、大刀的靈活跟戰斧的沈重破壞力\n"
            "﹐使得長戟成為許多戰士的最愛。\n");
    }
    setup();
}
