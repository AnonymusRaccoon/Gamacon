/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** system
*/

typedef struct gc_system gc_system;

#pragma once

#include "systems/texture_renderer_system.h"
#include "entity.h"
#include <stdbool.h>

struct gc_system
{
    const char *name;
    const char *component_name;
    bool (*check_dependencies)(const gc_system *, const gc_entity *);
    void (*update_entity)(gc_engine *engine, gc_entity *entity, float dtime);
    void (*destroy)(void *system);
};

bool system_check_dependencies(const gc_system *sys, const gc_entity *entity);
void system_destroy(void *system);