/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** deserializer
*/

#include <stdio.h>
#include "xml.h"
#include "read_line.h"
#include "utility.h"
#include "entity.h"
#include "engine.h"

gc_component *deserialize_component(gc_engine *engine, gc_entity *entity, \
gc_scene *scene, node *n)
{
    const void *model = engine->get_component(engine, n->name);
    gc_component *cmp = NULL;

    if (!model) {
        my_printf("Couldn't find a component with the name: %s\n", n->name);
        return (NULL);
    }
    cmp = new_component(model, 0, 0, 0, 0, 0, 0, 0);
    if (cmp->fdctr)
        cmp->fdctr(entity, scene, cmp, n);
    return (cmp);
}

gc_entity *deserialize_entity(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_entity *entity = NULL;
    gc_component *cmp = NULL;
    int id = xml_getintprop(n, "id");

    if (id > 0)
        entity = entity_create_with_id(id);
    else
        entity = entity_create();
    if (!entity)
        return (NULL);
    for (node *cmp_n = n->child; cmp_n; cmp_n = cmp_n->next) {
        cmp = deserialize_component(engine, entity, scene, cmp_n);
        entity->add_component(entity, cmp);
    }
    return (entity);
}