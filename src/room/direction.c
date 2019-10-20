#define DIRECTION_COUNT 6

enum Direction { NorthDirection, SouthDirection, EastDirection, WestDirection, UpDirection, DownDirection, NullDirection };

char *NORTH = "north";
char *SOUTH = "south";
char *EAST = "east";
char *WEST = "west";
char *UP = "up";
char *DOWN = "down";
char *BAD_DIRECTION = "";

typedef struct DirectionMap {
    enum Direction enum_direction;
    char *direction;
} DirectionMap;

typedef struct Directions {
    DirectionMap *map[DIRECTION_COUNT];
} Directions;

DirectionMap *create_direction_map(enum Direction enum_direction, char *direction) {
    DirectionMap *map = malloc(sizeof(DirectionMap));
    map->enum_direction = enum_direction;
    map->direction = direction;
    return map;
}

Directions *create_directions() {
    Directions *directions = malloc(sizeof(Directions));
    directions->map[0] = create_direction_map(NorthDirection, NORTH);
    directions->map[1] = create_direction_map(SouthDirection, SOUTH);
    directions->map[2] = create_direction_map(EastDirection, EAST);
    directions->map[3] = create_direction_map(WestDirection, WEST);
    directions->map[4] = create_direction_map(UpDirection, UP);
    directions->map[5] = create_direction_map(DownDirection, DOWN);
    return directions;
}

enum Direction get_direction_from_string(char *direction) {
    Directions *dir = create_directions();
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        if (strcmp(dir->map[i]->direction, direction) == 0) {
            return dir->map[i]->enum_direction;
        }
    }
    return NullDirection;
}

char *get_string_from_direction(enum Direction direction) {
    Directions *dir = create_directions();
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        if (dir->map[i]->enum_direction == direction) {
            return dir->map[i]->direction;
        }
    }
    return BAD_DIRECTION;
}
