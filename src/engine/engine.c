/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#include "engine.h"
#include "system.h"
#include "renderer.h"
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

void update_entity(gc_engine *engine, gc_entity *entity, float dtime)
{
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (((gc_system *)sys->data)->check_dependencies(sys->data, entity))
            ((gc_system *)sys->data)->update_entity(engine, entity, dtime);
    }
}

int game_loop(gc_engine *engine)
{
    gc_entity *entities = engine->scene->entities;
    float dtime = sfTime_asSeconds(sfClock_restart(engine->clock));

    handle_events(engine);
    for (gc_entity *entity = entities; entity; entity = entity->next)
        update_entity(engine, entity, dtime);
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
    sfSprite_destroy(engine->sprite);
    sfRenderWindow_destroy(engine->window);
    sfClock_destroy(engine->clock);
    free(engine);
}

int engine_create_sfdata(gc_engine *engine, char *title, unsigned framerate)
{
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;

    engine->window = sfRenderWindow_create(mode, title, style, NULL);
    engine->sprite = sfSprite_create();
    engine->clock = sfClock_create();
    if (!engine->window || !engine->sprite || !engine->clock)
        return (-1);
    sfRenderWindow_setFramerateLimit(engine->window, framerate);
    return (0);
}

gc_engine *engine_create(char *title, unsigned framerate)
{
    gc_engine *engine = malloc(sizeof(gc_engine));

    if (!engine)
        return (NULL);
    if (engine_create_sfdata(engine, title, framerate) < 0) {
        free(engine);
        return (NULL);
    }
    engine->is_open = &engine_is_open;
    engine->game_loop = &game_loop;
    engine->change_scene = &change_scene;
    engine->draw = &renderer_draw;
    engine->draw_texture = &renderer_draw_texture;
    engine->destroy = &engine_destroy;
    engine->scene = NULL;
    engine_add_buildin_systems(engine);
    engine_add_buildin_components(engine);
    return (engine);
}