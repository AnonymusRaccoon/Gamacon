/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** component
*/

typedef struct gc_component gc_component;

#pragma once

#include <stdarg.h>
#include "engine.h"

struct gc_component
{
    char *name;
    unsigned size;
    char **dependencies;
    void (*ctr)(void *component, va_list);
    void (*fdctr)(gc_engine *engine, void *component, node *n);
    void (*dtr)(void *component);
    char *(*serialize)(void *component);
    void (*destroy)(void *component);

    gc_component *next;
    gc_component *prev;
};

void *new_component(const void *component, ...);
void component_destroy(void *component);