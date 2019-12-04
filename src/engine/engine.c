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
    for (int i = 0; all_systems[i]; i++) {
        if (all_systems[i]->check_dependencies(all_systems[i], entity))
            all_systems[i]->update_entity(engine, entity);
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
    engine->scene = NULL;
    return (engine);
}