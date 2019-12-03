/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

#include "system.h"
#include "utility.h"
#include <stdlib.h>

const gc_system *all_systems[] = {
    &texture_renderer_system,
    NULL
};

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

const void *get_system(char *name)
{
    for (int i = 0; all_systems[i]; i++) {
        if (!my_strcmp(((const gc_system *)all_systems[i])->name, name))
            return (all_systems[i]);
    }
    return (NULL);
}

void system_destroy(void *component)
{
    free(component);
}