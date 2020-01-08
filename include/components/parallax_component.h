/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** parallax_component
*/

#pragma once

#include "component.h"

struct parallax_component
{
    gc_component base;
    gc_vector2 old_pos;
    float speed;
};

extern const struct parallax_component parallax_component;