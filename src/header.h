#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <libpq-fe.h>
#include <string.h>

#define MAX_ROOMS 12000
#define MAX_MOBS_PER_ROOM 50
#define MAX_EXITS 6

enum ActionType;
enum EventType;

/**
 * Game service
 */
typedef struct GameService GameServiceT;
typedef struct Action ActionT;
typedef struct Client ClientT;
void client_send_to_clients(GameServiceT *game_service, ClientT *client, char *buffer);
ClientT *get_client(GameServiceT *game_service, int i);
ActionT *get_action(GameServiceT *game_service, char *name_partial);

/**
 * Location Table
 */
typedef struct LocationTable LocationTableT;
LocationTableT *get_location_table(GameServiceT *game_service);

/**
 * Mobs
 */
typedef struct Mob MobT;
MobT *create_mob(int id, uuid_t uuid, char *name);

/**
 * Mob Table
 */
typedef struct MobTable MobTableT;
MobTableT *hydrate_mob_table(PGresult *result);

/**
 * Rooms
 */
typedef struct Room RoomT;
int get_room_id(RoomT *room);


/**
 * Room Table
 */
typedef struct RoomTable RoomTableT;
RoomTableT *hydrate_room_table(PGresult *result);

#include "room/direction.c"
#include "queries.h"
#include "db/db.h"
#include "mob/mob.h"
#include "room/room.h"
#include "game/location_table.c"
#include "action/action_type.c"
#include "request/request.c"
#include "socket/socket.h"
#include "action/action.h"
#include "event/event.h"
#include "game/game_service.h"
#include "event_consumers.h"
