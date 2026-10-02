// blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
	set_name("單刀", ({ "blade" }) );
	set_weight(8000);
	setup_blade(2, 10, 60, 0);

	if( !clonep() ) {
		set("wield_as", "blade" );
		set("unit", "把");
		set("value", 3500);
		set("rigidity", 25);
		set("long", "一把鋼鑄單刀﹐是武林中人常用的武器。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
