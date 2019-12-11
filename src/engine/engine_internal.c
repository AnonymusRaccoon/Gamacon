/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine_internal
*/

#include <stdbool.h>
#include "engine.h"

bool engine_is_open(gc_engine *engine)
{
    (void)engine;
    return (false);
}

void handle_events(gc_engine *engine)
{
    (void)engine;
}

void engine_draw(gc_engine *engine)
{
    (void)engine;
}

int change_scene(gc_engine *engine, gc_scene *scene)
{
    if (engine->scene)
        engine->scene->destroy(engine->scene);
    engine->scene = scene;
    return (0);
}