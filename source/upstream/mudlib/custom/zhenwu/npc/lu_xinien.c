#include <npc.h>
inherit F_VILLAGER;
void create(){ set_name("魯熙年", ({"lu xinien","lu","xinien","魯熙年"})); set_race("human"); set_class("soldier"); set("gender","male"); set("nickname","徵兵官"); set("long", "魯熙年是一名身材微胖的中年武官，兩眼瞇成一條線，臉上總帶著似笑非笑的古怪表情。他同時也是振武營負責招募新兵的徵兵官，看起來約三十多歲。至於入伍手續與條件，目前尚未接入，等待可靠資料補齊。\n"); setup(); }
