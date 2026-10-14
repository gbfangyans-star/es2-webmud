// wine_pot.c

inherit ITEM;

void create()
{
	object water;

	seteuid(getuid());
	set_name("大酒缸", ({ "wine pot", "pot" }));
	set_max_encumbrance(180000);
	set("long", "一個裝滿酒的大酒缸﹐如果你不怕醉死的話﹐儘管舀來喝(drink)。\n");
	set("no_get", 1);
	set("liquid_container", 1);
	setup();
	if( clonep() ) {
		water = new("/d/choyin/npc/obj/red_wine");
		water->set_volume(150000);
		water->move(this_object());
	}
}

int accept_object(object me, object ob) { return 1; }

// 補滿：酒被喝光時液體物件會消失，以前的 reset() 只補還在的，喝乾後就不會再有。
// 現在不見了就重新放一份，再補到滿；房間每次重生（reset）時也會呼叫。
void refill()
{
	object liquid;

	if( !(liquid = present("red wine", this_object())) ) {
		seteuid(getuid());
		liquid = new("/d/choyin/npc/obj/red_wine");
		liquid->move(this_object());
	}
	liquid->set_volume(150000);
}

void reset()
{
	refill();
}
