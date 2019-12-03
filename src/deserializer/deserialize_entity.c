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

gc_component *deserialize_component(int fd)
{
    char *component = read_line(fd);
    const gc_component *model;
    gc_component *cmp = NULL;
    char *p = my_strchr(component, ' ');
    char *args = component + (size_t)p + 1;

    if (!p)
        return (NULL);
    *p = '\0';
    model = get_component(component);
    if (!model)
        return (NULL);
    cmp = new_component(model, 0, 0, 0, 0, 0, 0, 0);
    cmp->fdctr(cmp, args);
    return (cmp);
}

gc_entity *deserialize_entity(int fd)
{
    gc_entity *entity = NULL;
    char *id_str = read_line(fd);
    int id = my_atoi(id_str);
    gc_component *cmp = NULL;

    if (id < 0)
        return (NULL);
    entity = entity_create_with_id(id);
    if (!entity)
        return (NULL);
    while ((cmp = deserialize_component(fd)))
        entity->add_component(entity, cmp);
    return (entity);
}