// /custom/zhenwu/obj/short_pike.c
// NEW（振武軍營新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 obj/area/obj/pike.c（長槍：weight 11000, value 6000, setup_pike(2,11,60,1)）為基礎，
// 縮短為軍中制式短槍：重量、售價各降，傷害參數改為 (2,9,80,2)。

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("短槍", ({ "short pike", "pike" }));
    set_weight(6000);
    setup_pike(2, 9, 80, 2);

    if( !clonep() ) {
        set("wield_as", ({ "twohanded pike", "pike" }));
        set("unit", "把");
        set("value", 4000);
        set("rigidity", 25);
        set("long", "軍中將士長備的制式武器，槍鋒森寒，頗有軍威。\n");
    }
    setup();
}
