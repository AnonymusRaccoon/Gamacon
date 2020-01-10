/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** engine_system_builder
*/

#include "engine.h"
#include "system.h"
#include "systems/sfml_renderer_system.h"
#include "systems/movable_system.h"
#include "systems/parallax_system.h"
#include "systems/controllers/keyboard_controller_system.h"
#include "systems/friction_system.h"
#include "systems/collision_system.h"
#include "systems/camerafollow_system.h"
#include "sfml_renderer.h"
#include <stdlib.h>

void engine_add_system(gc_engine *engine, const void *system)
{
    engine->systems = list_add(engine->systems, (void *)system);
}

void engine_finish_physics(gc_engine *engine)
{
    engine->add_system(engine, new_system(&movable_system));
}

void engine_add_buildin_systems(gc_engine *engine)
{
    engine->systems = NULL;
    engine->add_system = &engine_add_system;
    engine->get_system = &engine_get_system;
    engine->finish_physics = &engine_finish_physics;
    engine->add_system(engine, &parallax_system);
    engine->add_system(engine, &keyboard_controller_system);
    engine->add_system(engine, &friction_system);
    engine->add_system(engine, new_system(&collision_system, engine->scene));
}

int engine_use_sfml(gc_engine *engine, const char *title, int framerate)
{
    void *renderer = new_system(&sfml_renderer, engine, title, framerate);
    void *camfollow = new_system(&camerafollow_system);

    if (!renderer || !camfollow)
        return (-1);
    engine->add_system(engine, renderer);
    engine->add_system(engine, camfollow);
    engine->add_dataloader(engine, "music", &sfml_music_loader);
    engine->add_dataloader(engine, "sprite", &sfml_sprite_loader);
    engine->add_dataloader(engine, "font", &sfml_font_loader);
    return (0);
}