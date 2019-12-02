/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#include "engine.h"
#include "renderer.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

int game_loop(gc_engine *engine)
{
    handle_events(engine);
    engine->draw(engine);
    return (0);
}

gc_engine *engine_create(char *title)
{
    gc_engine *engine = malloc(sizeof(gc_engine));
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;

    engine->window = sfRenderWindow_create(mode, title, style, NULL);
    engine->is_open = &engine_is_open;
    engine->game_loop = &game_loop;
    engine->change_scene = &change_scene;
    engine->draw = &renderer_draw;
    return (engine);
}