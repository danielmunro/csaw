#include <string.h>

typedef struct {
    int id;
    Uuid uuid;
    char name[20];
} Mob;

Mob *new_mob(const int id, Uuid *uuid, const char name[20]) {
  Mob *m = malloc(sizeof(Mob));
  m->id = id;
  uuid_copy(m->uuid.uuid, uuid->uuid);
  strcpy(m->name, name);
  return m;
}

