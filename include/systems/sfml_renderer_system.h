/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer_system
*/

#pragma once

#include "system.h"
#include <SFML/Graphics.h>
#include "scene.h"
#include "text.h"
#include "systems/sfml_renderer_system.h"
#include "systems/camerafollow_system.h"

typedef struct sfml_renderer_system sf_renderer;
struct sfml_renderer_system
{
    gc_system system;
    sfRenderWindow *window;
    sfSprite *sprite;
    sfText *text;
    sfView *view;
    sfVertexArray *vertices;
    sfRenderStates *states;
    gc_vector2 (*get_text_size)(sf_renderer *this, gc_text *text);
    bool is_fullscreen;
};

gc_system *gc_new_sfml_renderer(gc_engine *engine, \
const char *title, int framerate);

extern const struct sfml_renderer_system sfml_renderer;