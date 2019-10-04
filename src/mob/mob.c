#include <string.h>

typedef struct Mob {
    int id;
    Uuid uuid;
    char name[20];
    RoomT *room;
} Mob;

Mob *create_mob(int id, UuidT *uuid, char *name) {
  Mob *m = malloc(sizeof(Mob));
  m->id = id;
  uuid_copy(m->uuid.uuid, uuid->uuid);
  strcpy(m->name, name);
  return m;
}
