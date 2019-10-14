#include <string.h>

typedef struct Mob {
    int id;
    uuid_t uuid;
    char *name;
    RoomT *room;
    char *canonical_id;
} Mob;

Mob *create_mob(int id, uuid_t uuid, char *name, char *canonical_id) {
  Mob *m = malloc(sizeof(Mob));
  m->id = id;
  uuid_copy(m->uuid, uuid);
  m->name = name;
  m->room = NULL;
  m->canonical_id = canonical_id;
  return m;
}
