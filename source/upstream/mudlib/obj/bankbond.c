// bankbond.c
//
// 舊的錢莊金契。錢莊現在把存款直接記在角色身上（"bank_account"），不再使用
// 金契。保留這個檔案，讓仍帶著舊金契的角色登入時能正常載入；載入後金契會
// 自行消失，不再存進登入自動載入清單。帳上的存款不受影響。

inherit ITEM;

void create()
{
	set_name("錢莊金契", ({ "bankbond" }));
	set_weight(1);
	if( !clonep() ) {
		set("unit", "張");
		set("long",
			"這是一張已經作廢的錢莊金契﹐錢莊現在把存款直接記在客人名下。\n");
		set("no_sell", 1);
		set("value", 1);
	}
	setup();
}

// 不再存進自動載入清單。
string query_autoload() { return 0; }

protected void expire()
{
	if( environment() )
		tell_object(environment(),
			"你身上的舊錢莊金契已經作廢﹐存款直接記在你的名下﹐可用 balance 查詢。\n");
	destruct(this_object());
}

void autoload(string param)
{
	call_out("expire", 1);
}
