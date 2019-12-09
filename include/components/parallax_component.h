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
    float speed;
};

extern const struct parallax_component parallax_component;