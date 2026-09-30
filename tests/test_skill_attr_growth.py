from pathlib import Path
import re

MUD = Path(__file__).resolve().parents[1] / 'source' / 'upstream' / 'mudlib'


def read(p):
    return (MUD / p).read_text(encoding='utf-8')


def test_hook_in_advance_skill():
    s = read('feature/char/skill.c')
    body = s[s.index('varargs void advance_skill(string skill, int amount)\n{'):]
    body = body[:body.index('\n}\n')]
    assert 'old_level = skills[skill];' in body
    assert 'roll_attr_growth(skill, old_level, skills[skill]);' in body


def test_growth_table_and_message():
    s = read('feature/char/skill.c')
    assert '#define ATTR_GROWTH_MAX 50' in s
    for line in ['if( value >= 45 ) return 10;', 'if( value >= 40 ) return 20;',
                 'if( value >= 30 ) return 30;', 'return 40;']:
        assert line in s
    assert 'attr_growth_base(value) * (100 + lv) / 2' in s
    assert '"attr_growth/" + skill' in s
    assert 'if( !userp(this_object()) ) return;' in s
    assert '"提高了！' in s


def test_skill_daemons():
    assert re.search(r'string growth_attr\(\)\s*\{\s*return 0;', read('std/skill.c'))
    assert re.search(r'string growth_attr\(\)\s*\{\s*return "str";', read('daemon/skill/unarmed.c'))
