/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** deserializer
*/

#include <stdio.h>
#include "read_line.h"
#include "utility.h"
#include "entity.h"
#include "engine.h"

gc_component *deserialize_component(gc_engine *engine, int fd)
{
    char *component = read_line(fd);
    const gc_component *model;
    gc_component *cmp = NULL;
    char *args;

    if (!component || my_strcmp(component, ""))
        return (NULL);
    args = my_strchr(component, ' ');
    if (!args)
        return (NULL);
    *args = '\0';
    args += 1;
    model = get_component(component);
    if (!model)
        return (NULL);
    cmp = new_component(model, 0, 0, 0, 0, 0, 0, 0);
    cmp->fdctr(engine, cmp, args);
    return (cmp);
}

gc_entity *deserialize_entity(gc_engine *engine, int fd)
{
    gc_entity *entity = NULL;
    char *id_str = read_line(fd);
    int id;
    gc_component *cmp = NULL;

    if (!id_str)
        return (NULL);
    id = my_atoi(id_str);
    if (id < 0)
        return (NULL);
    if (id > 0)
        entity = entity_create_with_id(id);
    else
        entity = entity_create();
    if (!entity)
        return (NULL);
    while ((cmp = deserialize_component(engine, fd)))
        entity->add_component(entity, cmp);
    return (entity);
}