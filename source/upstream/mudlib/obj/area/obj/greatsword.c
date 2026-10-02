

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("大劍", "great sword", "sword" );
    set_weight(24000);
    setup_sword(3, 13, 100, 5);

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 11000);
        set("rigidity", 25);
        set("long",
            "一把約五尺長的重劍﹐像這麼巨大的重劍多半是背在背後，只能由膂力\n"
            "過人的壯漢使用。\n");
        set("wield_msg", "$N將背後的劍囊一扯，「呼」地一聲抽出一把大劍。\n");
    }
    setup();
    // 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
    if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }

