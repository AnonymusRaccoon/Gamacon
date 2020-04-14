/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#pragma once

#include "component.h"
#include "tile.h"
#include <stdbool.h>

#define ROTATION_INFO 3

struct vertex
{
    int x;
    int y;
    int z;
};

struct vertex_component
{
    gc_component base;
    struct tile *map;
    struct vertex **vertices;
};

extern const struct vertex_component vertex_component;
bool vertex_serialize(struct vertex_component *this, const char *file);

sfVector2f sfvector2f(gc_vector2 vector);