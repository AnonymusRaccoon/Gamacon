/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** system
*/

typedef struct gc_system gc_system;

#pragma once

#include "entity.h"
#include <stdbool.h>
#include <stddef.h>

struct gc_system
{
    const char *name;
    const char *component_name;
    size_t size;
    void (*ctr)(void *system, va_list list);
    void (*dtr)(void *system);
    bool (*check_dependencies)(const gc_system *, const gc_entity *);
    void (*update_entity)(gc_engine *, void *system, gc_entity *, float dtime);
    void (*destroy)(void *system);
};

bool system_check_dependencies(const gc_system *sys, const gc_entity *entity);
void *new_system(const void *system, ...);
void system_destroy(void *system);