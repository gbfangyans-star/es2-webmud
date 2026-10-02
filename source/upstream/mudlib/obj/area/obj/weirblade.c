// weirblade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("大刀", ({ "weirblade", "blade" }) );
	set_weight(15000);
	setup_blade(2, 14, 60, 0);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "把");
		set("value", 6500);
		set("rigidity", 25);
		set("long", "又厚又重的大刀，令人望而生畏，如果雙手握持的話，威力更是強大。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
