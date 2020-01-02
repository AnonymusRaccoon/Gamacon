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
    int distance_down;
    int distance_top;
    int distance_left;
    int distance_right;
};

extern const struct collision_component collision_component;