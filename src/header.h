#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "uuid.c"
#include "mob/mob.h"
#ifndef MOCK
#include "db/db.h"
#endif
#include "action/action_type.c"
#include "request/request.c"
#include "action/action.h"
#include "socket/socket.h"
#include "event/event.h"
#include "game_service.c"
#include "socket/event_consumer/echo_event_consumer.c"
