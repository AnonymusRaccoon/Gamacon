/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** entity
*/

#include "entity.h"
#include <stdlib.h>

char *entity_serialize(gc_entity *entity)
{
    (void)entity;
    return (NULL);
}

void destroy(gc_entity *entity)
{
    gc_component *next = NULL;

    for (gc_component *cmp = entity->components; cmp; cmp = next) {
        next = cmp->next;
        cmp->destroy(cmp);
    }
    if (entity->tostr)
        free(entity->tostr);
    free(entity);
}