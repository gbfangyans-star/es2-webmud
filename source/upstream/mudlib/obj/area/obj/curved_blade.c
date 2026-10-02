// curved_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("彎刀", ({ "curved blade", "blade" }) );
	set_weight(9000);
	setup_blade(2, 12, 60, 0);

	if( !clonep() ) {
		set("wield_as", "blade" );
		set("unit", "把");
		set("value", 4200);
		set("rigidity", 25);
		set("long", "這是一種改良型的單刀，刀身較寬而彎，用於揮斬威力要比單刀大。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
