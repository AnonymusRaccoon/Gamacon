/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

typedef struct vertex {
    int x;
    int y;
    int z;
} vertex;

struct vertex_component
{
    vertex *vertices;
};

extern const struct vertex_component vertex_component;