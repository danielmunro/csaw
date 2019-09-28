typedef struct {
    uuid_t uuid;
} Uuid;

Uuid * uuid_from_string(char * uuid_string) {
    uuid_t uuid = {0};
    uuid_parse(uuid_string, uuid);
    Uuid *u = malloc(sizeof(Uuid));
    uuid_copy(u->uuid, uuid);
    return u;
}