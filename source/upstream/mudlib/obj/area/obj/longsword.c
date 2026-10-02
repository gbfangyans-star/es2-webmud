// longsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
	set_name("長劍", ({ "long sword", "sword" }) );
	set_weight(7500);
	setup_sword(2, 10, 50, 1);

	if( !clonep() ) {
		set("wield_as", "sword" );
		set("unit", "把");
		set("value", 4000);
		set("rigidity", 25);
		set("long", "一把約三尺長的長劍﹐是武林中人常用的武器。\n");
		set("wield_msg", "$N「唰」地一聲抽出一把長劍握在手中。\n");
	}
	setup();
	// 武器附加屬性：每把新產生的武器擲一次前綴／後綴（adm/daemons/enhanced.c）。
	if( clonep() ) ENHANCE_D->roll_affix(this_object());
}

// 附加屬性已在產生時決定，NPC 帶著時不再另外強化。
void varify_template(object owner) { }
