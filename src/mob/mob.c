#include <string.h>

typedef struct Mob {
    int id;
    uuid_t uuid;
    ObjectDescriptionT *description;
    RoomT *room;
    char *canonical_id;
} Mob;

Mob *create_mob(int id, uuid_t uuid, ObjectDescriptionT *object_description, char *canonical_id) {
  Mob *m = malloc(sizeof(Mob));
  m->id = id;
  uuid_copy(m->uuid, uuid);
  m->description = object_description;
  m->room = NULL;
  m->canonical_id = malloc(strlen(canonical_id));
  strcpy(m->canonical_id, canonical_id);
  return m;
}
