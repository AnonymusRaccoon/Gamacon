/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** engine_system_builder
*/

#include "engine.h"
#include "components/map_linker.h"
#include "components/movable_component.h"
#include "components/parallax_component.h"
#include "components/fixed_to_cam_component.h"
#include "components/renderer.h"
#include "components/camerafollow_component.h"
#include "components/transform_component.h"
#include "components/friction_component.h"
#include "components/friction_giver.h"
#include "components/collision_component.h"
#include "components/vertex_component.h"
#include "components/tooltip_component.h"
#include "components/clickable_component.h"
#include "components/tag_component.h"
#include "components/input_component.h"

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
    engine->add_component(engine, &renderer_component);
    engine->add_component(engine, &camerafollow_component);
    engine->add_component(engine, &fixed_to_cam);
    engine->add_component(engine, &parallax_component);
    engine->add_component(engine, &friction_giver);
    engine->add_component(engine, &friction_component);
    engine->add_component(engine, &collision_component);
    engine->add_component(engine, &clickable_component);
    engine->add_component(engine, &vertex_component);
    engine->add_component(engine, &input_component);
    engine->add_component(engine, &tag_component);
    engine->add_component(engine, &tooltip_component);
    engine->add_component(engine, &map_linker);
}