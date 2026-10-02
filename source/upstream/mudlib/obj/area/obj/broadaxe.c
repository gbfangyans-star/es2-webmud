// broadaxe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
	set_name("板斧", ({ "broadaxe", "axe" }) );
	set_weight(10000);
	setup_axe(2, 11, 100, 0);

	if( !clonep() ) {
		set("wield_as", ({ "axe", "twohanded axe" }) );
		set("unit", "把");
		set("value", 5000);
		set("rigidity", 25);
		set("long", "一把大面板斧，份量著實沉重，不過板斧的斧刃很長，是相當厲害的兵刃。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
