/* 交歡杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("交歡杖", ({ "staff of eroticism", "staff" }));
    set_weight(17300);
    init_damage(4, 13, 150, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一根奇異的雙手杖﹐杖身竟是一男一女兩具乾屍﹗兩具乾屍以交歡之勢\n"
            "合為杖身﹐兩個人頭恰好是杖頭。男女兩個人頭的口部似乎可以活動﹐\n"
            "不知暗藏了甚麼機關......\n");
        set("apply_weapon/twohanded staff", ([
            "armor": 20,
            "awarness": -50,
            "str": 3,
        ]));
    }
    setup();
}
