

inherit F_CLEAN_UP;

private void create() { seteuid(getuid()); }

int main(object me, string arg)
{
    mapping m;
    string sk, sk_m;

    if( !arg || arg == "" )
        return notify_fail("你要停用什麼技能？\n");

    if( me->is_busy() )
        return notify_fail("你正在忙著別的事, 無法專心。\n");

    // 學過的技能都可以停用，包括閃躲、招架、內功這類沒有技能檔的基本技能。
    if( !me->query_learn(arg) && !me->query_skill(arg, 1) )
        return notify_fail("你目前不會這項技能。\n");

    // 特殊武功被設定在哪些基本技能上，先全部拿掉，那些技能改回只用基本功夫。
    // 例如 disable tiger-blade：雙手刀法之後只使用基本的雙手刀法。
    m = me->query_skill_map();
    if( mapp(m) )
        foreach(sk, sk_m in m)
            if( sk != arg && sk_m == arg ) {
                me->map_skill(sk);
                write("你決定在「" + to_chinese(sk) + "」方面停止使用「" + to_chinese(arg) + "」。\n");
            }

    // 技能本身完全停用：例如 disable twohanded blade 後，裝備雙手刀不會出手攻擊。
    me->map_skill(arg, "none");
    write("你決定停止使用所學有關「" + to_chinese(arg) + "」的技巧。\n");
    return 1;
}

int help()
{
    write(@TEXT
指令格式：disable <技能>

這個指令讓你完全停止使用某種技能，學過的技能都可以停用。停用之後要再使用，
請用 enable <技能>。

例如：
  disable tiger-blade       不再使用瘋虎刀法，雙手刀只使用基本的雙手刀法。
  disable twohanded blade   停用雙手刀法，裝備雙手刀時不會出手攻擊。

其他相關指令：enable、skills
TEXT
    );
    return 1;
}

