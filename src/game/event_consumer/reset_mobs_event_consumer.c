void do_mob_reset(GameServiceT *game_service, MobResetT *reset) {
    int max_quantity = reset->max_quantity;
    int max_per_room = reset->max_per_room;
    if (game_service->location_table->rooms[reset->room->id]) {
//        for ()
    }
}

void reset_mobs(GameServiceT *game_service, Event *tick_event) {
//    for (int i = 0; i < MAX_MOBS; i++) {
//        if (game_service->mob_reset_table->resets[i]) {
//
//        }
//    }
}

EventConsumer *create_reset_mobs_event_consumer() {
    return create_event_consumer(TickEventType, reset_mobs);
}