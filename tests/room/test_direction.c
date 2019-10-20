void test_direction_enum_sanity_checks() {
    assert(get_direction_from_string(NORTH) == NorthDirection);
    assert(get_direction_from_string(SOUTH) == SouthDirection);
    assert(get_direction_from_string(EAST) == EastDirection);
    assert(get_direction_from_string(WEST) == WestDirection);
    assert(get_direction_from_string(UP) == UpDirection);
    assert(get_direction_from_string(DOWN) == DownDirection);
    assert(get_direction_from_string("NOT_DIRECTION") == NullDirection);
}

void test_direction_string_sanity_checks() {
    assert(strcmp(get_string_from_direction(NorthDirection), NORTH) == 0);
    assert(strcmp(get_string_from_direction(SouthDirection), SOUTH) == 0);
    assert(strcmp(get_string_from_direction(EastDirection), EAST) == 0);
    assert(strcmp(get_string_from_direction(WestDirection), WEST) == 0);
    assert(strcmp(get_string_from_direction(UpDirection), UP) == 0);
    assert(strcmp(get_string_from_direction(DownDirection), DOWN) == 0);
    assert(strcmp(get_string_from_direction(NullDirection), BAD_DIRECTION) == 0);
}
