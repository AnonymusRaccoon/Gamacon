/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** entity_factory
*/

#include "entity.h"
#include "component.h"
#include "my.h"
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

int entity_add(gc_scene *scene, gc_entity *e)
{
    char *name;

    scene->entities = list_add(scene->entities, e);
    if (!scene->entities)
        return (-1);
    for (gc_component *cmp = e->components; cmp; cmp = cmp->next) {
        name = cmp->name;
        scene->entities_by_cmp = tupple_add(scene->entities_by_cmp, name, e);
        if (!scene->entities_by_cmp)
            return (-1);
    }
    return (0);
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

void entity_remove_component(const gc_scene *scene, const gc_entity *entity, \
const char *name)
{
    gc_component *cmp;

    if (!scene || !entity || !entity->components)
        return;
    cmp = component_remove(entity->components, name);
    if (!cmp)
        return;
    for (gc_tupple *tup = scene->entities_by_cmp; tup; tup = tup->next) {
        if (!my_strcmp(tup->name, name))
            tup_remove(tup, entity->id);
    }
    component_destroy(cmp);
}