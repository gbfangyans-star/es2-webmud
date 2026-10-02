// glaive.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("鬼頭刀", ({ "glaive", "blade" }) );
	set_weight(9000);
	setup_blade(2, 10, 80, 0);

	if( !clonep() ) {
		set("wield_as", ({ "blade", "twohanded blade" }) );
		set("unit", "把");
		set("value", 6000);
		set("rigidity", 25);
		set("long",
			"鬼頭刀是一種背厚刃薄的大刀，刀身長而直，刀背特厚，雖然堅固耐用，份量\n卻是不輕。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
