/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** movable_component
*/

#pragma once

#include "component.h"

struct collision_component
{
    gc_component base;
    int layer;
};

extern const struct collision_component collision_component;