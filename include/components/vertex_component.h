/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct vertex
{
    int x;
    int y;
    int z;
};

struct tile
{
    char *texture_name;
    struct vertex *corners[4];
    void *texture;
    char data;
};

struct vertex_component
{
    gc_component base;
    struct tile *map;
    struct vertex **vertices;
};

extern const struct vertex_component vertex_component;