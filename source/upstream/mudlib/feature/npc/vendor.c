

#include <dbase.h>
#include <name.h>

static mapping stock;

private void
reset()
{
    if( !environment() ) return;
    stock = copy(query("merchandise"));
}

// affirm_merchandise()
//
// This is an apply function interfacing with the standard 'buy' command
// which is called when an player attemp to 'buy xxx from yyy' while xxx
// is passed via the parameter what and yyy is this_object() (must be
// present to the player). If we affirmed that we have such item for sell,
// buy_ob should return an string, or int, or anything that identifies
// this item we have in later bargain. Else, 0 is returned if we are not
// selling such item.

varargs mixed
affirm_merchandise(object buyer, string what, int amount)
{
    mapping list;
    string item, name_part;
    int i, index, count;

    if( amount < 1 ) amount = 1;
    // 「buy skin 2 from xxx」表示第二種叫 skin 的商品。sscanf 失敗時不能動到 what，
    // 否則像 "water skin" 這種有空格的名稱會被截成 "water"。
    if( sscanf(what, "%s %d", name_part, index) == 2 ) what = name_part;
    else index = 1;

    if( !mapp(list = query("merchandise")) )
	return notify_fail(name() + "並沒有賣 " + what + " 這種東西。\n");

    if( !mapp(stock) ) stock = copy(list);

    foreach(item, count in stock)
    {
	if( (!item->id(what)) || (--index) ) continue;
	if( stock[item] < 1 )
	    return notify_fail(item->name() + "已經賣完了﹐待會兒再來吧。\n");
	if( stock[item] < amount )
	    return notify_fail(item->name() + "只剩下" + chinese_number(stock[item])
		+ (item->query("base_unit") || item->query("unit") || "個") + "了。\n");
	return item;
    }

}

int
query_trading_price(string handle)
{
    mapping list;

    if( !mapp(list = query("merchandise")) )
	return 0;

    if( undefinedp(list[handle]) ) return 0;

    return handle->query("value");
}

// amount：一次買幾個。可堆疊的商品（COMBINED_ITEM）合成一堆交貨；其他商品一件一件交，
// 身上拿不動（太重或放不下）的部分直接銷毀，不掉在地上，庫存與價錢照算。
varargs void
deliver_merchandise(object me, string what, int amount)
{
    mapping list;
    string unit, item_name;
    object ob;
    int got, i;

    if ( !living(this_object()) ) return;

    list = query("merchandise");
    if( !mapp(list) || undefinedp(list[what]) ) return;
    if( amount < 1 ) amount = 1;

    ob = new(what);
    item_name = ob->query("name");

    if( ob->query_volume() ) {
	// Special process for liquid merchandise.
	object container_ob;
	string container;
	if( !(container = ob->query("default_container")) )
	    container = "/obj/bottle";
	for( i = 0; i < amount; i++ ) {
	    if( i ) ob = new(what);
	    container_ob = new(container);
	    unit = container_ob->query("container_unit");
	    ob->move(container_ob);
	    if( container_ob->move(me) ) got++;
	    else destruct(container_ob);
	}
    } else if( function_exists("set_amount", ob) ) {
	// 可堆疊：一次給一堆，拿不動就逐次減少數量，直到拿得動為止。
	unit = ob->query("base_unit") || ob->query("unit");
	got = amount;
	ob->set_amount(got);
	while( got > 0 && !ob->move(me) ) {
	    got--;
	    if( got > 0 ) ob->set_amount(got);
	}
	if( got == 0 ) destruct(ob);
    } else {
	unit = ob->query("unit");
	for( i = 0; i < amount; i++ ) {
	    if( i ) ob = new(what);
	    if( ob->move(me) ) got++;
	    else destruct(ob);
	}
    }

    if( !unit ) unit = "個";
    // 用 tell_object：店小二這類延遲交貨的商人，交貨時 this_player() 不一定是買家。
    tell_object(me, "你向" + name() + "買下" + chinese_number(amount) + unit + item_name + "。\n");
    if( got < amount )
	tell_object(me, "你身上拿不動，其中" + chinese_number(amount - got) + unit + item_name + "就這麼不見了。\n");

    // Reduce stock account;
    if( !mapp(stock) ) stock = copy(query("merchandise"));
    stock[what] -= amount;
}

private string
price_string(int v)
{
    if( v%10000 == 0 ) return chinese_number(v/10000) + "兩黃金";
    if( v%100 == 0 ) return chinese_number(v/100) + "兩銀子";
    return chinese_number(v) + "文錢";
}

int
do_vendor_list(string arg)
{
    mapping goods;
    string list, item;
    int count;

    if( !mapp(goods = query("merchandise")) ) return 0;
    if( arg && !id(arg) ) return 0;

    list = "";
    foreach(item, count in goods) {
	if( count < 1 ) continue;
	// MODIFIED: %-30s pads by raw char count, which goes ragged when a
	// name mixes Chinese (double-width) and ASCII; cjk_pad() counts
	// visual width instead so the "：" column and the price column both
	// line up. Not original ES2 wording, only the alignment logic.
	list += "  " + cjk_pad(item->short(1), 30) + "："
	    + cjk_pad(price_string(item->query("value")), 12, 1) + "\n";
    }
    if( list=="" ) {
	write( name() + "的貨物已經全部賣光了，下次早一點來吧！\n");
	return 1;
    }

    write("你可以購買下列這些東西：\n-------------------------\n" + list);
    return 1;
}

