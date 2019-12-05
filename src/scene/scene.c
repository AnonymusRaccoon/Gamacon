/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include "renderer.h"
#include "utility.h"
#include <stdlib.h>

int scene_add_entity(gc_scene *scene, gc_entity *entity)
{
    gc_entity *list;

    if (!scene || !entity)
        return (-1);
    list = scene->entities;
    if (!list) {
        scene->entities = entity;
    } else {
        while (list->next)
            list = list->next;
        list->next = entity;
        entity->prev = list;
    }
    return (1);
}

int scene_load_textures(gc_scene *scene, const char **textures)
{
    gc_texture *texture;
    int len = arraylen(textures) + 1;

    scene->textures = malloc(sizeof(gc_texture) * len);
    for (int i = 0; textures[i]; i++) {
        texture = texture_create(textures[i]);
        if (!texture)
            return (-1);
        scene->textures[i] = texture;
    }
    scene->textures[len - 1] = NULL;
    return (0);
}

void scene_destroy(gc_scene *scene)
{
    gc_entity *next = NULL;

    for (gc_entity *entity = scene->entities; entity; entity = next) {
        next = entity->next;
        entity->destroy(entity);
    }
    for (int i = 0; scene->textures[i]; i++) {
        scene->textures[i]->destroy(scene->textures[i]);
    }
    free(scene);
}

gc_scene *scene_create(const char **textures)
{
    gc_scene *scene = malloc(sizeof(gc_scene));

    if (!scene)
        return (NULL);
    scene->textures = NULL;
    if (textures && scene_load_textures(scene, textures) < 0)
        return (NULL);
    scene->entities = NULL;
    scene->add_entity = &scene_add_entity;
    scene->destroy = &scene_destroy;
    return (scene);
}