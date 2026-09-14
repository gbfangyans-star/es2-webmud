inherit ITEM;
inherit F_STUDY;
void create(){ set_name("測試書", "test book", "book"); set_weight(1000); set("required/skill",(["literate":1])); set("content",(["literate":10])); }
