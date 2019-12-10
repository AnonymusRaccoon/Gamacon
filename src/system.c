/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "system.h"
#include "utility.h"
#include <stdlib.h>

bool system_check_dependencies(const gc_system *sys, const gc_entity *entity)
{
    void *cmp = entity->get_component(entity, sys->component_name);
    gc_component *comp = (gc_component *)cmp;

    if (!comp)
        return (false);
    for (int i = 0; comp->dependencies[i]; i++) {
        if (!entity->has_component(entity, comp->dependencies[i]))
            return (false);
    }
    return (true);
}

const gc_system *engine_get_system(gc_engine *engine, const char *name)
{
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (!my_strcmp(((const gc_system *)sys->data)->name, name))
            return (sys->data);
    }
    return (NULL);
}

void system_destroy(void *system)
{
    free(system);
}