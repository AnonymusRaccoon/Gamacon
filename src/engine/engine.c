/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#include "engine.h"
#include "system.h"
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

void update_system(gc_engine *engine, gc_system *sys, float dtime)
{
    gc_scene *scene = engine->scene;
    gc_list *entities;

    if (!scene)
        return;
    entities = scene->get_entity_by_cmp(scene, sys->component_name);
    for (gc_list *entity = entities; entity; entity = entity->next) {
        if (sys->check_dependencies(sys, entity->data))
            sys->update_entity(sys, entity->data, dtime);
    }
}

int game_loop(gc_engine *engine, float dtime)
{
    engine->handle_events(engine);
    for (gc_list *sys = engine->systems; sys; sys = sys->next)
        update_system(engine, sys->data, dtime);
    engine->draw(engine);
    return (0);
}

void engine_destroy(gc_engine *engine)
{
    gc_list *next;

    if (engine->scene)
        engine->scene->destroy(engine->scene);
    for (gc_list *system = engine->systems; system; system = next) {
        next = system->next;
        ((gc_system *)system->data)->destroy(system->data);
        free(system);
    }
    free(engine);
}

gc_engine *engine_create()
{
    gc_engine *engine = malloc(sizeof(gc_engine));

    if (!engine)
        return (NULL);
    engine->scene = NULL;
    engine->is_open = &engine_is_open;
    engine->handle_events = &handle_events;
    engine->game_loop = &game_loop;
    engine->draw = &engine_draw;
    engine->change_scene = &change_scene;
    engine->destroy = &engine_destroy;
    engine_add_buildin_systems(engine);
    engine_add_buildin_components(engine);
    return (engine);
}