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
    engine->components = list_add(engine->components, (void *)component);
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