def tiger_growth(from_level, to_level):
    gin = kee = cor = 0
    for lv in range(max(from_level + 1, 21), to_level + 1):
        if lv >= 161:
            gin += 1; kee += 1
        elif lv >= 140:
            gin += 3; kee += 4
        else:
            gin += 2; kee += 2
        if lv == 100:
            cor += 2
    return gin, kee, cor


def powerup(skill):
    if skill < 100:
        return None
    return skill // 4, skill // 3, skill * 3 // 2


def test_five_virtual_tiger_force_players():
    players = [
        # name, from, to, expected growth, powerup at to
        ("虎徒甲", 20, 21, (2, 2, 0), None),
        ("虎徒乙", 99, 100, (2, 2, 2), (25, 33, 150)),
        ("虎徒丙", 120, 120, (0, 0, 0), (30, 40, 180)),
        ("虎徒丁", 139, 140, (3, 4, 0), (35, 46, 210)),
        ("虎徒戊", 160, 161, (1, 1, 0), (40, 53, 241)),
    ]
    for _, old, new, expected_growth, expected_powerup in players:
        assert tiger_growth(old, new) == expected_growth
        assert powerup(new) == expected_powerup
