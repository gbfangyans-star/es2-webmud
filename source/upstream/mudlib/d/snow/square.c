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
		// 暫時：衣服類護具展示用（custom/armor/cloth），查看完畢後移除。
		"/custom/armor/cloth/animitta_kasaya": 1,
		"/custom/armor/cloth/black_cloth": 1,
		"/custom/armor/cloth/black_dragon_dress": 1,
		"/custom/armor/cloth/black_mandarin_jacket": 1,
		"/custom/armor/cloth/black_robe": 1,
		"/custom/armor/cloth/black_suit": 1,
		"/custom/armor/cloth/blood_cloth": 1,
		"/custom/armor/cloth/blood_stained_cloth": 1,
		"/custom/armor/cloth/blue_dress": 1,
		"/custom/armor/cloth/broken_iron_cloth": 1,
		"/custom/armor/cloth/charm_robe": 1,
		"/custom/armor/cloth/cloth_of_sorrow": 1,
		"/custom/armor/cloth/cloudy_silk_cloth": 1,
		"/custom/armor/cloth/cowhide_vest": 1,
		"/custom/armor/cloth/crocodile_dress": 1,
		"/custom/armor/cloth/dark_cloth": 1,
		"/custom/armor/cloth/devilish_dress": 1,
		"/custom/armor/cloth/dragon_cloth": 1,
		"/custom/armor/cloth/embroidery_dress": 1,
		"/custom/armor/cloth/exorcist_cassock": 1,
		"/custom/armor/cloth/fire_wolf_cloak": 1,
		"/custom/armor/cloth/firewu_cloth": 1,
		"/custom/armor/cloth/force_cloth": 1,
		"/custom/armor/cloth/fur_sarong": 1,
		"/custom/armor/cloth/gold_robe": 1,
		"/custom/armor/cloth/golden_robe": 1,
		"/custom/armor/cloth/gray_robe": 1,
		"/custom/armor/cloth/gray_taoist_robe": 1,
		"/custom/armor/cloth/green_robe": 1,
		"/custom/armor/cloth/green_suit": 1,
		"/custom/armor/cloth/iron_cloth": 1,
		"/custom/armor/cloth/judge_robe": 1,
		"/custom/armor/cloth/leather_vest": 1,
		"/custom/armor/cloth/malik_robe": 1,
		"/custom/armor/cloth/omega_dress": 1,
		"/custom/armor/cloth/pink_dress": 1,
		"/custom/armor/cloth/purple_taoist_robe": 1,
		"/custom/armor/cloth/rain_dragon_skin": 1,
		"/custom/armor/cloth/rainbow_gown": 1,
		"/custom/armor/cloth/red_cloth": 1,
		"/custom/armor/cloth/red_robe": 1,
		"/custom/armor/cloth/red_scale_cloth": 1,
		"/custom/armor/cloth/seven_star_robe": 1,
		"/custom/armor/cloth/silk_cloth": 1,
		"/custom/armor/cloth/silkworm_tunic": 1,
		"/custom/armor/cloth/silver_cloth": 1,
		"/custom/armor/cloth/sky_earth_cloth": 1,
		"/custom/armor/cloth/soft_cloth": 1,
		"/custom/armor/cloth/straw_cloth": 1,
		"/custom/armor/cloth/tao_robe": 1,
		"/custom/armor/cloth/taoist_robe": 1,
		"/custom/armor/cloth/tender_cloth": 1,
		"/custom/armor/cloth/tiger_coat": 1,
		"/custom/armor/cloth/tigerish_robe": 1,
		"/custom/armor/cloth/tigerish_skin": 1,
		"/custom/armor/cloth/violet_cloth": 1,
		"/custom/armor/cloth/white_cloth": 1,
		"/custom/armor/cloth/white_robe": 1,
		"/custom/armor/cloth/white_scholar_dress": 1,
		"/custom/armor/cloth/white_taoist_robe": 1,
		"/custom/armor/cloth/yellow_and_black_cloth": 1,
		"/custom/armor/cloth/yellow_cloth": 1,
		"/custom/armor/cloth/yellow_suit": 1,
		"/d/snow/npc/obj/white_dress": 1,
		"/d/lee/obj/tight_cloth": 1,
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

