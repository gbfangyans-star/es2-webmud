

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("鐵鞭", ({ "rod", "rod" }) );
    set_weight(12000);
    setup_blunt(3, 8, 90, 2);

    if( !clonep() ) {
        set("wield_as", ({ "blunt" }));
        set("affix_short_name", "鞭");
        set("unit", "把");
        set("value", 5200);
        set("rigidity", 25);
        set("long", "一把沉重的鐵鞭，武林中常見的兵器。\n");
    }
    setup();
    // 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
    if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }

