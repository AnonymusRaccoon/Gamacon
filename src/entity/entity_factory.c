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
const gc_entity entity_prefab;

gc_entity *entity_create(void)
{
    gc_entity *entity = malloc(sizeof(gc_entity));

    if (!entity)
        return (NULL);
    *entity = entity_prefab;
    entity->id = next_id;
    next_id++;
    return (entity);
}

gc_entity *entity_create_with_id(int id)
{
    gc_entity *entity = malloc(sizeof(gc_entity));

    if (!entity)
        return (NULL);
    *entity = entity_prefab;
    entity->id = id;
    return (entity);
}

gc_entity *entity_add(gc_entity *list, gc_entity *entity)
{
    gc_entity *list_const = list;

    if (!list) {
        return (entity);
    } else {
        while (list->next)
            list = list->next;
        list->next = entity;
        entity->prev = list;
        return (list_const);
    }
}

gc_entity *entity_add_component(gc_entity *entity, void *component)
{
    gc_component *components = entity->components;

    if (!component)
        return (NULL);
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