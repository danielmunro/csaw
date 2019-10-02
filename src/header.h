#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <libpq-fe.h>

enum ActionType;
enum EventType;

typedef struct GameService GameServiceT;
typedef struct Action ActionT;
typedef struct Client ClientT;
void client_send_to_clients(GameServiceT *game_service, ClientT *client, char *buffer);
ClientT *get_client(GameServiceT *game_service, int i);
ActionT *get_action(GameServiceT *game_service, char *name_partial);

typedef struct Uuid UuidT;

typedef struct Mob MobT;
MobT *create_mob(int id, UuidT *uuid, char *name);

typedef struct MobTable MobTableT;
MobTableT *hydrate_mob_table(PGresult *result);

#include "uuid.c"
#include "query.h"
#include "db/db.h"
#include "mob/mob.h"
#include "action/action_type.c"
#include "request/request.c"
#include "socket/socket.h"
#include "action/action.h"
#include "event/event.h"
#include "game_service.c"
#include "event_consumer.h"
