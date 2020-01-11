/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** entity
*/

typedef struct gc_entity gc_entity;

#pragma once

#include "component.h"
#include "vector2.h"
#include <stdbool.h>

struct gc_entity
{
    int id;
    gc_component *components;
    gc_entity *(*add_component)(gc_entity *entity, void *component);
    void *(*get_component)(const gc_entity *entity, const char *name);
    bool (*has_component)(const gc_entity *entity, const char *name);
    void (*remove_component)(const gc_scene *scene, const gc_entity *entity, \
const char *name);
    char *(*serialize)(gc_entity *entity, int fd);
    void (*destroy)(gc_entity *entity);
};

gc_entity *entity_create(void);
gc_entity *entity_create_with_id(int id);
gc_entity *entity_get(gc_scene *scene, int id);
int entity_add(gc_scene *scene, gc_entity *entity);
gc_entity *entity_add_component(gc_entity *entity, void *component);
void *entity_get_component(const gc_entity *entity, const char *name);
void entity_remove_component(const gc_scene *scene, const gc_entity *entity, \
const char *name);
char *entity_serialize(gc_entity *entity, int fd);