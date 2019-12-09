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

gc_component *deserialize_component(gc_engine *engine, node *n)
{
    const gc_component *model;
    gc_component *cmp = NULL;


    model = get_component(n->name);
    if (!model)
        return (NULL);
    cmp = new_component(model, 0, 0, 0, 0, 0, 0, 0);
    cmp->fdctr(engine, cmp, n);
    return (cmp);
}

gc_entity *deserialize_entity(gc_engine *engine, node *n)
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
        cmp = deserialize_component(engine, cmp_n);
        entity->add_component(entity, cmp);
    }
    return (entity);
}