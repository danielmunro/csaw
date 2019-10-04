char *query_all_rooms = "SELECT id, uuid, name FROM room_entity";
char *query_room_exits = "SELECT `direction`, `destinationId` FROM exit_entity WHERE `sourceId` = ?";
