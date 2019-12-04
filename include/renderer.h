/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** renderer
*/

#pragma once

#include "engine.h"

void renderer_draw(gc_engine *engine);
gc_texture *texture_create(const char *path);
void renderer_draw_texture(gc_engine *engine, gc_texture *text, gc_vector2 pos);