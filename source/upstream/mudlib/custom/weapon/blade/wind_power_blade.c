/* 清風刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("清風刀", ({ "wind-power blade", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "『清風拂水魚波盪, 白雲繞頸情花開』, 清風刀白雲槍乃泰武定國兩大名兵,\n"
            "泰武定國接鄰南方蠻夷, 經年侵擾紛爭不斷, 朝廷中人為振武立威, 鑄此二兵\n"
            ". 清風刀鋒利柄實, 通體泛藍光而空心, 體長而輕, 揮武起來有如清風拂面,\n"
            "涼風陣陣, 清爽無比.\n");
        set("apply_weapon/blade", ([
            "attack": 10,
        ]));
    }
    setup();
}
