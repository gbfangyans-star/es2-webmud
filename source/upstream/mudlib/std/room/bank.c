// bank.c
//
// 錢莊：存款直接記在角色身上（"bank_account"，單位為文），不需要開戶，
// 也不需要金契。deposit 存款、withdraw 提款、convert 兌換；
// 查詢存款用全域的 balance 指令（cmds/std/balance.c），任何地方都能查。
// 以前發出的錢莊金契已經不再使用，玩家在錢莊存提款或查詢時會被收回，
// 帳上的存款不受影響。

#include <command.h>

inherit ROOM;

// Normalize player-facing money names to canonical money object ids.
// The bank sign is written in Chinese, while the original code only accepted
// coin/silver/gold. Accept both so WebMUD players do not fall through to What?.
string normalize_money_id(string money)
{
    if( !stringp(money) ) return money;
    switch(money) {
    case "coin": case "coins": case "coin_money":
    case "錢": case "文": case "文錢": case "銅錢": case "錢幣": case "銅幣":
        return "coin";
    case "silver": case "silver_money":
    case "銀": case "銀子": case "碎銀":
        return "silver";
    case "gold": case "gold_money": case "ingot":
    case "金": case "金子": case "黃金":
        return "gold";
    }
    return money;
}

// Resolve money by canonical money_id first, then legacy ids.  This avoids
// depending on present("*_money") alone and also rejects non-currency objects
// that happen to use an id such as "coin" (e.g. ancient coin quest items).
object find_player_money(object who, string money)
{
    object ob;
    string id;

    id = normalize_money_id(money);
    foreach(ob in all_inventory(who)) {
        if( !inherits(MONEY, ob) ) continue;
        if( ob->query("money_id") == id ) return ob;
        if( ob->id(id + "_money") ) return ob;
    }
    return 0;
}

string money_file(string money)
{
    string id;
    id = normalize_money_id(money);
    if( id!="coin" && id!="silver" && id!="gold" ) return 0;
    return "/obj/money/" + id;
}

// 存款的顯示格式與 balance 指令共用。
string money_string(int amount)
{
    return BALANCE_CMD->money_string(amount);
}

// 收回舊的錢莊金契並存檔（讓金契從登入自動載入清單中移除）。
// 存款本來就記在角色身上，收回金契不影響帳上的錢。
void retire_bankbond(object who)
{
    object bond;
    int retired;

    while( (bond = present("bankbond", who)) ) {
        destruct(bond);
        retired++;
    }
    if( retired ) {
        tell_object(who, "錢莊收回了你的舊金契﹐以後存款直接記在你的名下。\n");
        who->save();
    }
}

void init()
{
    ::init();
    add_action("do_convert", "convert");
    add_action("do_deposit", "deposit");
    add_action("do_withdraw", "withdraw");
    add_action("do_new_account", "open");
}

// 舊的開戶指令：現在不需要開戶了。
int do_new_account(string arg)
{
    if( !arg || arg!="account" ) return 0;
    retire_bankbond(this_player());
    write("錢莊的存款直接記在你的名下﹐不需要開戶﹐直接用 deposit 存款即可。\n");
    return 1;
}

int do_convert(string arg)
{
    string from, to;
    int amount, bv1, bv2;
    object from_ob, to_ob;

    if( !arg || sscanf(arg, "%d %s to %s", amount, from, to)!=3 )
        return notify_fail("指令格式﹕convert <數量> <貨幣種類> to <貨幣種類>\n");

    from = normalize_money_id(from);
    to = normalize_money_id(to);

    seteuid(getuid());
    from_ob = find_player_money(this_player(), from);
    to_ob = find_player_money(this_player(), to);
    if( !money_file(to) )
        return notify_fail("你想兌換哪一種錢﹖可用：文錢、碎銀、黃金。\n");

    if( !from_ob )        return notify_fail("你身上沒有這種貨幣。\n");
    if( amount < 1 )    return notify_fail("兌換貨幣一次至少要兌換一個。\n");

    if( (int)from_ob->query_amount() < amount )
        return notify_fail("你身上沒有那麼多" + from_ob->name() + "。\n");

    bv1 = from_ob->query("base_value");
    if( !bv1 ) return notify_fail("這種東西不值錢。\n");

    bv2 = to_ob ? to_ob->query("base_value") : call_other(money_file(to), "query", "base_value" );
    if( !bv2 ) return notify_fail("你要兌換哪一種貨幣﹖\n");

    if( bv1 < bv2 ) amount -= amount % (bv2 / bv1);
    if( amount==0 )    return notify_fail("這些" + from_ob->name() + "的價值太低了﹐換不起。\n");

    if( !to_ob ) {
        to_ob = new(money_file(to));
        to_ob->move(this_player());
        to_ob->set_amount(amount * bv1 / bv2);
    } else
        to_ob->add_amount(amount * bv1 / bv2);

    message_vision( sprintf("$N從身上取出%s%s%s﹐換成%s%s%s。\n",
        chinese_number(amount), from_ob->query("base_unit"), from_ob->name(),
        chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"), to_ob->name()),
        this_player() );

    from_ob->add_amount(-amount);

    return 1;
}

int do_deposit(string arg)
{
    int amount, value;
    string money;
    object money_ob;

    seteuid(getuid());
    retire_bankbond(this_player());

    if( !arg || sscanf(arg, "%d %s", amount, money)!=2 )
        return notify_fail("指令格式﹕deposit <數量> <貨幣種類>。\n");

    if( amount <= 0 )
        return notify_fail("你至少要存入一個錢幣。\n");

    money = normalize_money_id(money);
    if( !(money_ob = find_player_money(this_player(), money)) )
        return notify_fail("你身上沒有這種錢幣。可用：文錢、碎銀、黃金。\n");

    if( money_ob->query_amount() < amount )
        return notify_fail("你身上沒有這麼多的" + money_ob->name() + "。\n");

    value = amount * money_ob->query("base_value");
    write("你將" + chinese_number(amount) + money_ob->query("base_unit")
        + money_ob->name() + "存進錢莊。\n");
    this_player()->add("bank_account", value);
    money_ob->add_amount( - amount );
    write("你在錢莊的存款共有" + money_string(this_player()->query("bank_account"))
        + "。\n");
    this_player()->save();
    return 1;
}

int do_withdraw(string arg)
{
    int amount;
    string money;
    object money_ob;

    seteuid(getuid());
    retire_bankbond(this_player());

    if( !arg || sscanf(arg, "%d %s", amount, money)!=2 )
        return notify_fail("指令格式﹕withdraw <數量> <貨幣種類>。\n");

    if( amount <= 0 )
        return notify_fail("你至少要提領一個錢幣。\n");

    money = normalize_money_id(money);
    if( amount > 30000)
        return notify_fail("你不能一次領太多。\n");

    if( !money_file(money) )
        return notify_fail("你要提領哪一種錢﹖可用：文錢、碎銀、黃金。\n");

    if( catch(money_ob = new(money_file(money))) )
        return notify_fail("錢莊暫時無法取出這種貨幣，請通知管理員。\n");

    money_ob->set_amount(amount);
    if( this_player()->query("bank_account") < money_ob->value() ) {
        destruct(money_ob);
        return notify_fail("你的存款沒有這麼多錢。\n");
    }

    this_player()->add("bank_account", - money_ob->value());
    if( !money_ob->move(this_player()) ) {
        this_player()->add("bank_account", money_ob->value());
        destruct(money_ob);
        return notify_fail("你身上帶不了這許多錢﹐提少一點吧。\n");
    }

    write("錢莊將" + chinese_number(amount) + money_ob->query("base_unit")
        + money_ob->name() + "交給你。\n");
    write("你在錢莊的存款還有" + money_string(this_player()->query("bank_account"))
        + "。\n");
    this_player()->save();
    return 1;
}
