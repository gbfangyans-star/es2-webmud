// shortsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("短劍", ({ "short sword", "sword" }) );
	set_weight(4000);
	setup_sword(1, 15, 40, 1);

	if( !clonep() ) {
		set("wield_as", ({ "sword", "secondhand sword" }));
		set("unit", "把");
		set("value", 900);
		set("rigidity", 20);
		set("long", "一把粗糙的短劍﹐一般旅人帶在身邊防身用的武器。\n");
		set("wield_msg", "$N抽出一把短劍當作武器。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
