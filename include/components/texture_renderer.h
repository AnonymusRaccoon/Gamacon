/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#pragma once

#include "component.h"
#include "texture.h"
#include "vector2.h"

struct texture_renderer
{
    gc_component base;
    gc_texture *texture;
};

extern const struct texture_renderer texture_renderer;