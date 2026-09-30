/* 天之哀思 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("天之哀思", ({ "cloth of sorrow", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 45000);
        set("long",
            "這是一件很容易被人遺忘的戰袍。也許是因為戰袍也厭倦了主人終日忙碌\n"
            "的生活﹐也許是因為戰袍也會為死在自己主人手中的失敗者哀傷﹐這件戰\n"
            "袍所散發而出的怨氣是讓人難以忍受的。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "attack": 30,
            "defense": 20,
        ]));
    }
    setup();
}
