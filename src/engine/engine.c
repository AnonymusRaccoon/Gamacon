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

void update_entity(gc_engine *engine, gc_entity *entity)
{
    for (gc_list *sys = engine->systems; sys; sys = sys->next) {
        if (((gc_system *)sys->data)->check_dependencies(sys->data, entity))
            ((gc_system *)sys->data)->update_entity(engine, entity);
    }
}

int game_loop(gc_engine *engine)
{
    gc_entity *entities = engine->scene->entities;

    handle_events(engine);
    for (gc_entity *entity = entities; entity; entity = entity->next)
        update_entity(engine, entity);
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
    free(engine);
}

gc_engine *engine_create(char *title)
{
    gc_engine *engine = malloc(sizeof(gc_engine));
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;

    if (!engine)
        return (NULL);
    engine->window = sfRenderWindow_create(mode, title, style, NULL);
    engine->sprite = sfSprite_create();
    if (!engine->window || !engine->sprite)
        return (NULL);
    engine->is_open = &engine_is_open;
    engine->game_loop = &game_loop;
    engine->change_scene = &change_scene;
    engine->draw = &renderer_draw;
    engine->draw_texture = &renderer_draw_texture;
    engine->destroy = &engine_destroy;
    engine->scene = NULL;
    engine->systems = NULL;
    engine->add_system = &engine_add_system;
    engine_add_buildin_systems(engine);
    return (engine);
}