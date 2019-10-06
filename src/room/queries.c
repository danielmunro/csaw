char *query_all_rooms = "SELECT id, uuid, name FROM room_entity";
char *query_room_exits = "SELECT id, `sourceId`, `destinationId`, `direction` FROM exit_entity WHERE `sourceId` = ";
