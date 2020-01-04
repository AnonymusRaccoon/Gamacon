/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** collision_component
*/

#pragma once

struct collision_component
{
    gc_component base;
    float distance_down;
    float distance_top;
    float distance_left;
    float distance_right;
    int layer;
};

extern const struct collision_component collision_component;