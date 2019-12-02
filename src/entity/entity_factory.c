/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** entity_factory
*/

#include "entity.h"
#include "component.h"
#include <stdlib.h>

static unsigned int next_id = 0;

gc_entity *entity_create(void)
{
    gc_entity *entity = malloc(sizeof(gc_entity));

    if (!entity)
        return (NULL);
    entity->id = next_id;
    entity->components = NULL;
    entity->serialize = &entity_serialize;
    entity->next = NULL;
    entity->prev = NULL;
    next_id++;
    return (entity);
}

gc_entity *entity_add_component(gc_entity *entity, void *component)
{
    gc_component *components = entity->components;

    if (!components)
        entity->components = component;
    else {
        while (components->next)
            components = components->next;
        ((gc_component *)component)->prev = components;
        components->next = component;
    }
    return (entity);
}