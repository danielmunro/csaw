void do_mob_reset(GameServiceT *game_service, MobResetT *reset) {
    int max_quantity = reset->max_quantity;
    int max_per_room = reset->max_per_room;
    if (!game_service->location_table->rooms[reset->room->id]) {
        return;
    }
    int quantity = count_mob_instances(game_service->mob_table, reset->mob);
    int in_room = count_mobs_in_room_by_mob(game_service->location_table, reset->mob);
    if (quantity >= max_quantity || in_room >= max_per_room) {
        return;
    }
    // create copy of mob
    return;
}

void reset_mobs(GameServiceT *game_service, Event *tick_event) {
    for (int i = 0; i < MAX_MOB_RESETS; i++) {
        if (!game_service->mob_reset_table->resets[i]) {
            return;
        }
        do_mob_reset(game_service, game_service->mob_reset_table->resets[i]);
    }
}

EventConsumer *create_reset_mobs_event_consumer() {
    return create_event_consumer(TickEventType, reset_mobs);
}