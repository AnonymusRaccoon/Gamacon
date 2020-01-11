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
#include "entity.h"

struct gc_component
{
    char *name;
    unsigned size;
    char **dependencies;
    void (*ctr)(void *component, va_list);
    void (*fdctr)(gc_entity *entity, gc_scene *scene, void *component, node *n);
    void (*dtr)(void *component);
    char *(*serialize)(void *component);
    void (*destroy)(void *component);

    gc_component *next;
    gc_component *prev;
};

void *new_component(const void *component, ...);
void component_destroy(void *component);
gc_component *component_remove(gc_component *cmp, const char *name);

#define GETCMP(x) ((struct x *)entity->get_component(entity, #x))
#define GETCOLCMP(x) ((struct x *)entity_get_component(entity_get(engine->scene, id), #x))