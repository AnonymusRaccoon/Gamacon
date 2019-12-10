/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** engine_system_builder
*/

#include "engine.h"
#include "system.h"
#include "components/movable_component.h"
#include "components/parallax_component.h"
#include "components/texture_renderer.h"
#include "components/transform_component.h"
#include <stdlib.h>

void engine_add_component(gc_engine *engine, const void *component)
{
    gc_list *components = engine->components;

    if (!components) {
        engine->components = malloc(sizeof(gc_list));
        if (!engine->components)
            return;
        engine->components->data = (void *)component;
        engine->components->next = NULL;
    } else {
        while (components->next)
            components = components->next;
        components->next = malloc(sizeof(gc_list));
        if (!components->next)
            return;
        components->next->data = (void *)component;
        components->next->next = NULL;
    }
}

void engine_add_buildin_components(gc_engine *engine)
{
    engine->components = NULL;
    engine->add_component = &engine_add_component;
    engine->get_component = &engine_get_component;
    engine->add_component(engine, &transform_component);
    engine->add_component(engine, &movable_component);
    engine->add_component(engine, &texture_renderer);
    engine->add_component(engine, &parallax_component);
}