/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** engine
*/

#include "engine.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

int game_loop(gcEngine *engine)
{
    handle_events(engine);
    (void)engine;
    return (0);
}

gcEngine *create_engine(char *title)
{
    gcEngine *engine = malloc(sizeof(gcEngine));
    sfVideoMode mode = {800, 600, 32};
    sfWindowStyle style = sfDefaultStyle;

    engine->renderer.window = sfRenderWindow_create(mode, title, style, NULL);
    engine->is_open = &engine_is_open;
    engine->game_loop = &game_loop;
    engine->change_scene = &change_scene;
    return (engine);
}