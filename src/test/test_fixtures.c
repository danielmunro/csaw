int mob_fixture_id = 0;

Mob *create_test_mob() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    Mob *mob = create_mob(
            mob_fixture_id,
            uuid,
            "test mob",
            "canonical_id");
    mob_fixture_id++;
    return mob;
}

Room *create_test_room() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    Room *room = create_room(0, uuid, "test room");
    return room;
}

void create_test_area(GameServiceT *game_service) {
    Room *room1 = create_test_room();
    Room *room2 = create_test_room();
    room1->exits[0] = create_exit(0, room1, room2, NorthDirection);
    room2->exits[0] = create_exit(0, room2, room1, SouthDirection);
    game_service->room_table->rooms[0] = room1;
    game_service->room_table->rooms[1] = room2;
}
