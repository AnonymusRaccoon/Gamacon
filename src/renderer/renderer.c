/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** render
*/

#include "engine.h"
#include <SFML/Graphics.h>


void renderer_draw(gc_engine *engine)
{
    sfRenderWindow_clear(engine->window, sfBlack);
    sfRenderWindow_display(engine->window);
}