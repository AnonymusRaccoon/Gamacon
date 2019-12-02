/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** scene
*/
typedef struct gc_scene gc_scene;

#pragma once

#include "entity.h"
#include "texture.h"
#include <stdbool.h>

struct gc_scene
{
    gc_entity *entity_list;
    gc_texture **textures;
    int (*add_entity)(gc_engine *engine, struct gc_scene *scene);
};

gc_scene *scene_create(char **textures);
void scene_add_entity(gc_scene *scene, gc_entity *entity);

