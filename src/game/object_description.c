typedef struct ObjectDescription {
    char *name;
    char *brief;
    char *description;
} ObjectDescription;

ObjectDescription *create_object_description(char *name, char *brief, char *description) {
    ObjectDescription *object_description = malloc(sizeof(ObjectDescription));
    object_description->name = malloc(strlen(name));
    strcpy(object_description->name, name);
    object_description->brief = malloc(strlen(brief));
    strcpy(object_description->brief, brief);
    object_description->description = malloc(strlen(description));
    strcpy(object_description->description, description);
    return object_description;
}

char *get_object_name(ObjectDescription *o) {
    return o->name;
}

char *get_object_brief(ObjectDescription *o) {
    return o->brief;
}
