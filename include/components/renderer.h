/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#pragma once

#include "component.h"
#include "sprite.h"
#include "vector2.h"

enum GC_TEXTURETYPE {
    GC_TEXTUREREND
};

struct renderer
{
    gc_component base;
    gc_sprite *sprite;
    enum GC_TEXTURETYPE type;
};

extern const struct renderer renderer_component;