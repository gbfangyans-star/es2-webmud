// broadsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("闊劍", ({ "broadsword", "sword" }) );
	set_weight(10000);
	setup_sword(2, 12, 70, 1);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "twohanded sword"}) );
		set("unit", "把");
		set("value", 5500);
		set("rigidity", 25);
		set("long", "一把約三尺長的闊劍﹐份量不輕，需要不小的膂力才能揮舞這種武器。\n");
		set("wield_msg", "$N「唰」地一聲抽出一把又長又重的闊劍握在手中。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
