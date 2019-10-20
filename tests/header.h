#include <assert.h>
#include "../src/header.h"
#include "../src/test/test_fixtures.c"
#include "../src/test/test_suite.c"

// tests
#include "socket/event_consumer/test_dummy_login_event_consumer.c"
#include "socket/test_socket.c"
#include "socket/test_client.c"
#include "event/test_event_dispatcher.c"
#include "game/test_game_service.c"
#include "action/test_actions.c"
#include "room/test_room.c"
#include "room/test_direction.c"
