/* 鱷神戰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;32m鱷神戰袍\x1b[m", ({ "crocodile dress", "dress" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "這是一件用巨鱷王鱷皮製成的戰袍，相傳江渲少年時，亦水河畔傳聞\n"
            "出現一群巨鱷為患鄉里，失去牲畜時有所聞，生人被鱷群襲擊亦有之\n"
            "江渲聞此消息，遂與親族十數人前往除之，花了七晝夜，終於擊斃群\n"
            "鱷，唯獨為首的巨鱷王，身長二十餘尺，龐然大物，怪力異常不說，\n"
            "其鱷皮之厚，更非平常兵刃能傷，眾人圍攻之而不可取，在大伙都已\n"
            "精疲力盡，只剩江渲獨力與之搏鬥之時，一黑衣少年手中刀光一閃，\n"
            "隨即翩然而去。在江渲驚異之際，一股刀氣從巨鱷王額間迸發而出。\n"
            "鱷王死後，江渲取其皮製成數件器物，此鱷神戰袍便是其一。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "cor": 2,
            "twohanded blunt": 10,
            "armor": 10,
        ]));
    }
    setup();
}
