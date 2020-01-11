/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** entity
*/

#include "entity.h"
#include "utility.h"
#include <stdlib.h>
#include <unistd.h>

gc_entity *entity_get(gc_scene *scene, int id)
{
    if (!scene)
        return (NULL);
    for (gc_list *ent = scene->entities; ent; ent = ent->next) {
        if (((gc_entity *)ent->data)->id == id)
            return (ent->data);
    }
    return (NULL);
}

void *entity_get_component(const gc_entity *entity, const char *name)
{
    if (!entity || !name)
        return (NULL);
    for (gc_component *cmp = entity->components; cmp; cmp = cmp->next) {
        if (!my_strcmp(cmp->name, name))
            return (cmp);
    }
    return (NULL);
}

bool entity_has_component(const gc_entity *entity, const char *name)
{
    for (gc_component *cmp = entity->components; cmp; cmp = cmp->next) {
        if (!my_strcmp(cmp->name, name))
            return (true);
    }
    return (false);
}

char *entity_serialize(gc_entity *entity, int fd)
{
    char *id = tostr(entity->id);

    write(fd, id, my_strlen(id));
    write(fd, ": ", 2);
    for (gc_component *cmp = entity->components; cmp; cmp = cmp->next)
        cmp->serialize(cmp);
    free(id);
    return (NULL);
}

static void destroy(gc_entity *entity)
{
    gc_component *next = NULL;

    for (gc_component *cmp = entity->components; cmp; cmp = next) {
        next = cmp->next;
        cmp->destroy(cmp);
    }
    free(entity);
}

const gc_entity entity_prefab = {
    id: 0,
    components: NULL,
    add_component: &entity_add_component,
    get_component: &entity_get_component,
    has_component: &entity_has_component,
    remove_component: &entity_remove_component,
    serialize: &entity_serialize,
    destroy: &destroy
};