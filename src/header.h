#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
enum ActionType;
typedef struct GameService GameServiceT;
typedef struct Client ClientT;
ClientT *get_client(GameServiceT *game_service, int i);
#include "uuid.c"
#include "mob/mob.h"
#include "db/db.h"
#include "action/action_type.c"
#include "request/request.c"
#include "socket/socket.h"
#include "action/action.h"
#include "event/event.h"
#include "game_service.c"
#include "event_consumer.h"
