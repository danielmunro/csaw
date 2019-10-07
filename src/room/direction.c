enum Direction { NorthDirection, SouthDirection, EastDirection, WestDirection, UpDirection, DownDirection, NullDirection };

enum Direction get_direction_from_string(char *direction) {
    if (strcmp(direction, "north") == 0) {
        return NorthDirection;
    } else if (strcmp(direction, "south") == 0) {
        return SouthDirection;
    } else if (strcmp(direction, "east") == 0) {
        return EastDirection;
    } else if (strcmp(direction, "west") == 0) {
        return WestDirection;
    } else if (strcmp(direction, "up") == 0) {
        return UpDirection;
    } else if (strcmp(direction, "down") == 0) {
        return DownDirection;
    }
    return NullDirection;
}

char *get_string_from_direction(enum Direction direction) {
    if (direction == NorthDirection) {
        return "north";
    } else if (direction == SouthDirection) {
        return "south";
    } else if (direction == EastDirection) {
        return "east";
    } else if (direction == WestDirection) {
        return "west";
    } else if (direction == UpDirection) {
        return "up";
    } else if (direction == DownDirection) {
        return "down";
    }
    return "";
}
