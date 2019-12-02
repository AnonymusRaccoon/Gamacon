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
#include <stdbool.h>

struct gc_scene
{
    gc_entity *entities;
    gc_texture **textures;
    int (*add_entity)(gc_scene *scene, gc_entity *entity);
    void (*destroy)(gc_scene *scene);
};

gc_scene *scene_create(const char **textures);
int scene_add_entity(gc_scene *scene, gc_entity *entity);

