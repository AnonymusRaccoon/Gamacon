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
    gc_vector2 offset;
};

extern const struct fixed_to_cam fixed_to_cam;