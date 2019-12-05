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

    if (!cmp)
        return (false);
    for (gc_component *dep = comp->dependencies; dep; dep = comp->next) {
        if (!entity->has_component(entity, dep->name))
            return (false);
    }
    return (true);
}

const void *get_system(gc_engine *engine, char *name)
{
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (!my_strcmp(((const gc_system *)sys->data)->name, name))
            return (sys);
    }
    return (NULL);
}

void system_destroy(void *system)
{
    free(system);
}