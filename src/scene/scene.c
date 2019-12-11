/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include "utility.h"
#include "texture.h"
#include <stdlib.h>

gc_list *get_entity_by_cmp(gc_scene *scene, const char *cmp_name)
{
    for (gc_tupple *tup = scene->entities_by_cmp; tup; tup = tup->next) {
        if (!my_strcmp(tup->name, cmp_name))
            return (tup->entities);
    }
    return (NULL);
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
    gc_list *next = NULL;

    for (gc_list *entity = scene->entities; entity; entity = next) {
        next = entity->next;
        ((gc_entity *)entity->data)->destroy(entity->data);
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
    scene->entities_by_cmp = NULL;
    scene->add_entity = &entity_add;
    scene->get_entity = &entity_get;
    scene->get_entity_by_cmp = &get_entity_by_cmp;
    scene->destroy = &scene_destroy;
    return (scene);
}