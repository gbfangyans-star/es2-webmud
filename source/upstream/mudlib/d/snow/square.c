// Room: /d/snow/square.c

inherit ROOM;

void create()
{
	set("short", "廣場中央");
	set("long", @LONG
這裡是雪亭鎮廣場的中央﹐一株巨大的老榕樹盤根錯結地站在中央
﹐一些孩童常常爬上這株老榕嬉戲﹐榕樹下七橫八豎地放著幾張長凳供
人歇息聊天﹐樹旁還有一個水缸供路人取水解渴。
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/obj/pot" : 1,
		__DIR__"npc/gammer" : 1,
		__DIR__"npc/junkman": 1,
		"/custom/ghost/npc/hungry_ghost": 2,
		// 暫時：刀類武器展示用（custom/weapon/blade），查看完畢後移除。
		"/custom/weapon/blade/black_kris": 1,
		"/custom/weapon/blade/blade_of_dragon": 1,
		"/custom/weapon/blade/blade_of_dragon_awakened": 1,
		"/custom/weapon/blade/blade_of_fire_spirit": 1,
		"/custom/weapon/blade/blade_of_hydra_bone": 1,
		"/custom/weapon/blade/blade_of_inferno": 1,
		"/custom/weapon/blade/blade_of_nine_rings": 1,
		"/custom/weapon/blade/blade_of_strange_iron": 1,
		"/custom/weapon/blade/blood_blade": 1,
		"/custom/weapon/blade/blue_poison_blade": 1,
		"/custom/weapon/blade/ceremonial_moon": 1,
		"/custom/weapon/blade/cloudy_ring_blade": 1,
		"/custom/weapon/blade/colosus_blade": 1,
		"/custom/weapon/blade/copper_blade": 1,
		"/custom/weapon/blade/cursed_blade_of_darkness": 1,
		"/custom/weapon/blade/devilish_blade": 1,
		"/custom/weapon/blade/evil_lopsided_blade": 1,
		"/custom/weapon/blade/feather_blade": 1,
		"/custom/weapon/blade/fire_gods_wings": 1,
		"/custom/weapon/blade/flame_weapon": 1,
		"/custom/weapon/blade/flame_weapon_forged": 1,
		"/custom/weapon/blade/ghost_blade": 1,
		"/custom/weapon/blade/ghost_head_blade": 1,
		"/custom/weapon/blade/ghosts_blade": 1,
		"/custom/weapon/blade/grin_weapon": 1,
		"/custom/weapon/blade/horse_twohanded_blade": 1,
		"/custom/weapon/blade/large_blade": 1,
		"/custom/weapon/blade/moon_blade": 1,
		"/custom/weapon/blade/poison_wind_blade": 1,
		"/custom/weapon/blade/purple_dragon_blade": 1,
		"/custom/weapon/blade/reckless_blade": 1,
		"/custom/weapon/blade/snow_blade": 1,
		"/custom/weapon/blade/steelblade": 1,
		"/custom/weapon/blade/styx_blade": 1,
		"/custom/weapon/blade/test_heart_blade": 1,
		"/custom/weapon/blade/tiger_blade": 1,
		"/custom/weapon/blade/white_blade": 1,
		"/custom/weapon/blade/wind_power_blade": 1,
		"/custom/weapon/blade/wind_slasher_blade": 1,
		"/custom/weapon/blade/wing_blade": 1,
	]));
	set("detail", ([ /* sizeof() == 2 */
		"榕樹" : "這株榕樹少說也有兩三百歲了﹐一條條長長的鬚根幾乎垂到地面﹐
樹幹因為經常被人撫摸而顯得光滑。
",
		"長凳" : "十分普通常見的長凳﹐如果你累了﹐不必客氣﹐盡管做下來休息。
",
]));
	set("exits", ([ /* sizeof() == 4 */
		"east" : __DIR__"square_e",
		"north" : __DIR__"square_n",
		"west" : __DIR__"square_w",
		"south" : __DIR__"square_s",
	]));

	set("map/area", "雪亭鎮");
    setup();
}

void init()
{
	add_action("do_climb", "climb");
}

int do_climb(string arg)
{
	if( arg != "榕樹" ) return 0;

	message_vision("$N攀著榕樹的樹幹爬了上去。\n", this_player());
	if( this_player()->move(__DIR__"tree") )
		message("vision", this_player()->name() + "從樹下爬了上來。\n",
		environment(this_player()), this_player());
	return 1;
}

