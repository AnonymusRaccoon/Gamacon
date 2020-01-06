/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** collision_component
*/

#pragma once

#include "engine.h"
#include "entity.h"
#include <stdbool.h>

struct collision_component
{
    gc_component base;
    float distance_down;
    float distance_top;
    float distance_left;
    float distance_right;
    int layer;
    void (**on_collide)(gc_engine *engine, gc_entity *entity, int id);
    int collide_size;
};

typedef void (*collide_listener)(gc_engine *, gc_entity *, int);

void add_on_collide(struct collision_component *, collide_listener);

extern const struct collision_component collision_component;