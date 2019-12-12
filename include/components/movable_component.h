/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"
#include <stdbool.h>

struct movable_component
{
    gc_component base;
    bool moving_left;
    bool moving_right;
    int speed;
};

extern const struct movable_component movable_component;