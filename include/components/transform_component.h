/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** position_component
*/

#pragma once

#include "component.h"
#include "vector2.h"

struct transform_component
{
    gc_component base;
    gc_vector2 position;
    gc_vector2 size;
};

extern const struct transform_component transform_component;