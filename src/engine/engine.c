/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#include "engine.h"
#include "system.h"
#include "utility.h"
#include <stdlib.h>
#include "event_manager.h"

void update_system(gc_engine *engine, gc_system *sys, float dtime)
{
    gc_scene *scene = engine->scene;
    gc_list *entities;

    if (!scene)
        return;
    entities = scene->get_entity_by_cmp(scene, sys->component_name);
    for (gc_list *entity = entities; entity; entity = entity->next) {
        if (scene != engine->scene)
            return;
        if (sys->check_dependencies(sys, entity->data) && sys->update_entity)
            sys->update_entity(engine, sys, entity->data, dtime);
        else if (sys->update_entity)
            my_printf("Entity %d does not have all the required components \
for the system %s\n", ((gc_entity *)entity->data)->id, sys->name);
    }
}

int game_loop(gc_engine *engine, float dtime)
{
    gc_scene *scene = engine->scene;

    if (!engine->has_focus(engine))
        return (0);
    engine->handle_events(engine);
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (engine->scene != scene)
            return (0);
        update_system(engine, sys->data, dtime);
    }
    engine->draw(engine);
    return (0);
}

void engine_destroy(gc_engine *engine)
{
    gc_list *next;

    if (engine->scene)
        engine->scene->destroy(engine->scene);
    for (gc_list *dl = engine->dataloaders; dl; dl = next) {
        next = dl->next;
        free(dl->data);
        free(dl);
    }
    for (gc_list *system = engine->systems; system; system = next) {
        next = system->next;
        ((gc_system *)system->data)->destroy(system->data, engine);
        free(system);
    }
    for (gc_list *cmp = engine->components; cmp; cmp = next) {
        next = cmp->next;
        free(cmp);
    }
    free(engine);
}

gc_engine *engine_create_more(gc_engine *engine)
{
    engine->get_cursor_pos = &engine_get_cursor_pos;
    return (engine);
}

gc_engine *engine_create(void)
{
    gc_engine *engine = malloc(sizeof(gc_engine));

    if (!engine)
        return (NULL);
    engine->scene = NULL;
    engine->should_close = false;
    engine->is_open = &engine_is_open;
    engine->has_focus = &engine_has_focus;
    engine->is_keypressed = &engine_is_keypressed;
    engine->handle_events = &handle_events;
    engine->game_loop = &game_loop;
    engine->draw = &engine_draw;
    engine->change_scene = &change_scene;
    engine->play_music = &engine_play_music;
    engine->stop_music = &engine_stop_music;
    engine->destroy = &engine_destroy;
    engine_setup_event(engine);
    engine_add_builtin_systems(engine);
    engine_add_buildin_components(engine);
    engine_init_dataloaders(engine);
    return (engine_create_more(engine));
}