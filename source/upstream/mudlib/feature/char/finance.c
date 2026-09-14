// finance.c
// CUSTOM ECONOMY CONVENIENCE PATCH:
// Spending is value-based and automatically returns canonical change.
// This removes the need to visit a bank merely to break denominations.

private int query_carried_money_value()
{
    object ob;
    int total;

    total = 0;
    ob = present("gold_money", this_object());
    if (ob) total += (int)ob->value();
    ob = present("silver_money", this_object());
    if (ob) total += (int)ob->value();
    ob = present("coin_money", this_object());
    if (ob) total += (int)ob->value();

    return total;
}

private void set_money_amount(string type, int amount)
{
    object ob;

    ob = present(type + "_money", this_object());

    if (amount < 1) {
        if (ob) ob->set_amount(0);
        return;
    }

    if (!ob) {
        ob = new("/obj/money/" + type);
        ob->set_amount(amount);
        if (!ob->move(this_object())) {
            destruct(ob);
            error("finance: unable to return money/change to character.\n");
        }
        return;
    }

    ob->set_amount(amount);
}

private void set_carried_money_value(int value)
{
    int gold, silver, coin;

    if (value < 0) value = 0;

    gold = value / 10000;
    value %= 10000;
    silver = value / 100;
    coin = value % 100;

    set_money_amount("gold", gold);
    set_money_amount("silver", silver);
    set_money_amount("coin", coin);
}

varargs int
pay_money(int amount, int check_only)
{
    int total;

    if (amount < 1) return 1;

    total = query_carried_money_value();
    if (total < amount) return 0;

    // CUSTOM: any combination of denominations may pay a purchase.
    // On actual payment, normalize the remaining value into gold/silver/coin,
    // which is equivalent to the merchant returning exact change.
    if (!check_only)
        set_carried_money_value(total - amount);

    return 1;
}

// can_afford()
//
// CUSTOM semantics:
// 0: cannot afford the price.
// 1: total carried money is enough; exact change is handled automatically.
// Legacy return value 2 ("needs smaller change") is intentionally retired.

int can_afford(int amount) { return pay_money(amount, 1); }
