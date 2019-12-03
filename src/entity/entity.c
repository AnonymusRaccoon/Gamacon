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

void destroy(gc_entity *entity)
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
    serialize: &entity_serialize,
    destroy: &destroy,
    next: NULL,
    prev: NULL
};