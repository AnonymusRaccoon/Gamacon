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
        if (!entity->has_component(entity, comp->dependencies[i])) {
            my_printf("\tMissing component: %s\n\n", comp->dependencies[i]);
            return (false);
        }
    }
    return (true);
}

void *engine_get_system(gc_engine *engine, const char *name)
{
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (!my_strcmp(((const gc_system *)sys->data)->name, name))
            return (sys->data);
    }
    return (NULL);
}

void *new_system(const void *system, ...)
{
    gc_system *base = (gc_system *)system;
    va_list args;
    void *new_sys = malloc(base->size);

    if (!new_sys)
        return (NULL);
    *(gc_system *)new_sys = *base;
    if (((gc_system *)new_sys)->ctr) {
        va_start(args, system);
        ((gc_system *)new_sys)->ctr(new_sys, args);
        va_end(args);
    }
    return (new_sys);
}

void system_destroy(void *system)
{
    gc_system *sys = (gc_system *)system;

    if (sys->dtr)
        sys->dtr(system);
    free(system);
}