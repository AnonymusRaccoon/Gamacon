/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** engine_system_builder
*/

#include "engine.h"
#include "system.h"
#include "systems/texture_renderer_system.h"
#include <stdlib.h>

void engine_add_system(gc_engine *engine, const gc_system *system)
{
    gc_list *systems = engine->systems;

    if (!systems) {
        engine->systems = malloc(sizeof(gc_list));
        engine->systems->data = (void *)system;
        engine->systems->next = NULL;
    } else {
        while (systems->next)
            systems = systems->next;
        systems->next = malloc(sizeof(gc_list));
        systems->next->data = (void *)system;
        systems->next->next = NULL;
    }
}

void engine_add_buildin_systems(gc_engine *engine)
{
    engine->add_system(engine, &texture_renderer_system);
}