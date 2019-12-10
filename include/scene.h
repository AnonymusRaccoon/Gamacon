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
#include "texture.h"
#include "list.h"
#include "tupple.h"
#include <stdbool.h>

struct gc_scene
{
    gc_texture **textures;
    void (*destroy)(gc_scene *scene);

    gc_list *entities;
    gc_tupple *entities_by_cmp;
    int (*add_entity)(gc_scene *scene, gc_entity *entity);
    gc_entity *(*get_entity)(gc_scene *scene, int id);
    gc_list *(*get_entity_by_cmp)(gc_scene *scene, const char *cmp_name);
};

gc_scene *scene_create(const char **textures);
int scene_add_entity(gc_scene *scene, gc_entity *entity);

