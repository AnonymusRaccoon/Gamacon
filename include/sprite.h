/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** sprite
*/

#pragma once

#include "texture.h"
#include "vector2.h"
#include <SFML/Graphics.h>

typedef struct gc_int_rect
{
    float height;
    float width;
    float top;
    float left;
} gc_int_rect;

typedef struct gc_sprite {
    gc_texture *texture;
    gc_int_rect rect;
    gc_vector2 pos;
    gc_vector2 size;
} gc_sprite;