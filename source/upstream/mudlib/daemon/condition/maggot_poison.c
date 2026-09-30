/* CUSTOM WEAPON CONDITION: 附骨之蛆之毒 (maggot_poison)
 *
 * 2 tick 發作一次，共 5 次。每次：gin 目前值 -10、實格 -8、kee 目前值 -8、實格 -5、sen 目前值 -4、實格 -3。
 * 共用規則見 custom/condition/weapon_poison.c。
 */
inherit "/custom/condition/weapon_poison";

string poison_msg() { return "你感到一陣噁心，嘔出一灘帶血的膿痰，裡面竟然有幾隻蛆蟲蠕蠕而動！"; }
int burst_ticks() { return 2; }
int burst_count() { return 5; }
mixed *burst_damage()
{
    // ({ 屬性, 實格扣, 目前值扣 })
    return ({
        ({ "gin", 8, 10 }),
        ({ "kee", 5, 8 }),
        ({ "sen", 3, 4 }),
    });
}
