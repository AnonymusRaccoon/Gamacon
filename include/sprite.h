/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** sprite
*/

#pragma once

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
    void *texture;
    gc_int_rect rect;
    gc_vector2 pos;
    gc_vector2 scale;
} gc_sprite;

typedef struct gc_anim {
    char *name;
    int frame_count;
    float frame_rate;
    gc_int_rect rect;
} gc_anim;

typedef struct gc_animholder {
    gc_sprite *sprite;
    gc_anim *anims;
    int animcount;

    gc_anim *current;
    float timesince_up;
} gc_animholder;