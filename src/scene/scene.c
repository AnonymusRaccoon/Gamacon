/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include <stdbool.h>

void scene_add_entity(gc_scene *scene, gc_entity *entity)
{
    gc_entity *list;

    if (!scene)
        return;
    list = scene->entity_list;
    if (!list) {
        scene->entity_list = entity;
    } else {
        while (list->next)
            list = list->next;
        list->next = entity;
        entity->prev = list;
    }
}

bool scene_load_textures(gc_scene *scene, char **textures)
{
    gc_texture *texture;

    for (int i = 0; textures[i]; i++) {
        texture = renderer_load_texture(textures[i]);
        if (!texture)
            return (NULL);
        scene->textures[i] = texture;
    }
}

gc_scene *scene_create(char **textures)
{
    gc_scene *scene = malloc(sizeof(gc_scene));

    if (!scene)
        return (NULL);
    if (!scene_load_textures(scene, textures))
        return (NULL);
    scene->entity_list = NULL;
    scene->add_entity = &scene_add_entity;
    return (scene);
}