/* CUSTOM WEAPON CONDITION: 紫金鳳頭錐之毒 (phoenix_poison)
 *
 * 2 tick 發作一次，共 5 次。每次：gin 最大值 -4、目前值 -2、kee 最大值 -5、目前值 -3。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你的傷口一陣痠麻，一股黑血從傷口湧出"; }
int burst_ticks() { return 2; }
int burst_count() { return 5; }
mixed *burst_damage()
{
    return ({
        ({ "gin", 4, 2 }),
        ({ "kee", 5, 3 }),
    });
}
