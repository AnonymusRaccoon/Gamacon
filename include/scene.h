/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** scene
*/
typedef struct gc_scene gc_scene;

#pragma once

#include "engine.h"
#include "entity.h"
#include "list.h"
#include "tupple.h"
#include <stdbool.h>

struct gc_scene
{
    gc_list *data;
    void *(*get_data)(gc_scene *scene, const char *type, const char *name);

    void (*destroy)(gc_scene *scene);

    gc_list *entities;
    gc_tupple *entities_by_cmp;
    int (*add_entity)(gc_scene *scene, gc_entity *entity);
    gc_entity *(*get_entity)(gc_scene *scene, int id);
    gc_list *(*get_entity_by_cmp)(gc_scene *scene, const char *cmp_name);
    void (*load_entity)(gc_scene *this, gc_engine *engine, node *xml, int pref);

	gc_list *callbacks;
	callback_t (*get_callback)(gc_scene *this, char *name);

	bool is_paused;
};

callback_t scene_get_callback(gc_scene *scene, char *name);
gc_scene *scene_create(gc_engine *engine, const char *mappath);
void scene_load_data(gc_engine *engine, gc_scene *scene, node *n);
void *scene_get_data(gc_scene *scene, const char *type, const char *name);
void scene_destroy(gc_scene *scene);
void scene_load_entity(gc_scene *this, gc_engine *engine, node *n, int prefab);