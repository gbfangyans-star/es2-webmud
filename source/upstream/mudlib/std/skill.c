

inherit F_CLEAN_UP;

void setup()
{
    seteuid(getuid());
}

string type()
{
    return "martial";
}

// 技能升級時有機會增加的屬性（見 feature/char/skill.c），沒有則傳回 0。
string growth_attr()
{
    return 0;
}



