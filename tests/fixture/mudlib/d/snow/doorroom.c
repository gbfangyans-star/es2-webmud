inherit ROOM;
void create(){
 set("short","門房");
 set("exits", ([ "west": __DIR__ "a" ]));
 create_door("west","木門","east",DOOR_CLOSED);
}
