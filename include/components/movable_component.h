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
    gc_vector2 acceleration;
    gc_vector2 velocity;
};

extern const struct movable_component movable_component;