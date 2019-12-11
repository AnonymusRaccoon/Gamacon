/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#pragma once

#include "system.h"
#include <SFML/Graphics.h>

typedef struct sfml_renderer_system sfml_renderer_system;
struct sfml_renderer_system
{
    gc_system system;
    sfRenderWindow *window;
    sfSprite *sprite;
};

gc_system *gc_new_sfml_renderer(gc_engine *engine, \
const char *title, int framerate);
bool sfml_is_open(gc_engine *engine);
bool sfml_has_focus(gc_engine *engine);
bool sfml_is_keypressed(int key);
void sfml_handle_events(gc_engine *engine);
void sfml_draw(gc_engine *engine);