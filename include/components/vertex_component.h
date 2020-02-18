/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** vertex_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct vertex_component
{
    gc_component base;
    int **vertices;
};

extern const struct vertex_component vertex_component;