/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct controllable_component
{
    gc_component base;
    bool moving_left;
    bool moving_right;
    bool jumping;
};

extern const struct controllable_component controllable_component;