#include <npc.h>
#include <ansi.h>
inherit F_VILLAGER;

void create()
{
    set_name("假人", ({"target stake","stake","假人"}));
    set_race("human");
    set_class("commoner");
    set_level(20);
    set("civilized", 1);
    set("training_dummy", 1);
    set("long", "這是一具軍營內供新兵練武的粗麻木樁，樁身佈滿刀痕與箭孔。它被牢牢固定在地面，不會還手，也不會因操練而損壞，正適合反覆磨練基本招式。\n");
    setup();
}

int accept_fight(object who) { return 1; }

/* Training target never retaliates. */
void fight_ob(object ob) { }
void kill_ob(object ob) { }

/* Training target never dodges or parries. */
int defend(int ability, int strength, object from) { return 0; }
int absorb(int ability, int strength, object from) { return 0; }
int resist_damage(int damage, object from_ob) { return 0; }

/* Return a positive hit so hit-triggered learned EXP is awarded, but do not
 * change kee/HP/effective stats. */
varargs int receive_damage(int damage, object from, object attacker)
{
    if( damage < 1 ) damage = 1;
    return damage;
}

void die() { }
