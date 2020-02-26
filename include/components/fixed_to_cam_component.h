/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"
#include "vector2.h"

struct fixed_to_cam
{
    gc_component base;
    gc_vector2 pos;
    bool per_x;
    bool per_y;
    bool set_size;
};

extern const struct fixed_to_cam fixed_to_cam;