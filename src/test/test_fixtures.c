int mob_fixture_id = 0;

Mob *create_test_mob() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    Mob *mob = create_mob(
            mob_fixture_id,
            uuid,
            create_object_description("test_mob", "test mob", "test mob"),
            "canonical_id");
    mob_fixture_id++;
    return mob;
}

ClientT *create_test_client() {
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(3490);
    ClientT *client = new_client(myaddr, 0);
    client->mob = create_test_mob();
    return client;
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
    Room *room3 = create_test_room();
    Room *room4 = create_test_room();
    room1->exits[0] = create_exit(0, room1, room2, NorthDirection);
    room1->exits[1] = create_exit(0, room1, room3, EastDirection);
    room1->exits[2] = create_exit(0, room1, room4, UpDirection);
    room2->exits[0] = create_exit(0, room2, room1, SouthDirection);
    room3->exits[0] = create_exit(0, room3, room1, WestDirection);
    room4->exits[0] = create_exit(0, room4, room1, DownDirection);
    game_service->room_table->rooms[0] = room1;
    game_service->room_table->rooms[1] = room2;
    game_service->room_table->rooms[2] = room3;
    game_service->room_table->rooms[3] = room4;
}

GameServiceT *create_game_service_with_test_area() {
    GameServiceT *g = create_game_service();
    create_test_area(g);
    return g;
}
