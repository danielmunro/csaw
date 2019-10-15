#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <libpq-fe.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define MAX_ROOMS 12000
#define MAX_MOBS_PER_ROOM 50
#define MAX_EXITS 6

enum ActionType;
enum EventType;
int DEBUG;

/**
 * Game service
 */
typedef struct GameService GameServiceT;
typedef struct Action ActionT;
typedef struct Client ClientT;
typedef struct Server ServerT;
void client_send_to_clients(GameServiceT *game_service, ClientT *client, char *buffer);
ClientT *get_client(GameServiceT *game_service, int i);
ActionT *get_action(GameServiceT *game_service, char *name_partial);
ServerT *get_server(GameServiceT *game_service);

/**
 * Location Table
 */
typedef struct LocationTable LocationTableT;
LocationTableT *get_location_table(GameServiceT *game_service);

/**
 * Mobs
 */
typedef struct MobReset MobResetT;
typedef struct Mob MobT;
MobT *create_mob(int id, uuid_t uuid, char *name, char *canonical_id);
ClientT *get_client_from_mob(GameServiceT *game_service, MobT *mob); // game service
MobT *get_mob_by_id(GameServiceT *game_service, int id); // game service
int count_mobs_in_room_by_mob(LocationTableT *location_table, MobT *mob); // location table

typedef struct MobResetTable MobResetTableT;

typedef struct MobTable MobTableT;
MobTableT *hydrate_mob_table(PGresult *result);
MobResetTableT *hydrate_mob_reset_table(GameServiceT *game_service, PGresult *result);

/**
 * Rooms
 */
typedef struct Room RoomT;
int get_room_id(RoomT *room);
RoomT *get_room_by_id(GameServiceT *game_service, int id); // game service

/**
 * Room Table
 */
typedef struct RoomTable RoomTableT;
RoomTableT *hydrate_room_table(PGresult *result);

/**
 * Actions
 */
typedef struct Request RequestT;
void do_look_action(GameServiceT *game_service, RequestT *request);

/**
 * Events
 */
 typedef struct EventConsumer EventConsumerT;
typedef struct Event EventT;
void dispatch_event(GameServiceT *game_service, EventT *event);
EventT *create_login_event(ClientT *client);

EventConsumerT *create_input_to_action_event_consumer();
EventConsumerT *create_dummy_login_event_consumer();
EventConsumerT *create_pulse_to_tick_event_consumer();
EventConsumerT *create_increment_ticks_event_consumer();

#include "log/log_utility.c"
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
