/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** renderer_loader
*/

#include "engine.h"
#include "texture.h"
#include "utility.h"
#include <SFML/Graphics.h>
#include <stdlib.h>


gc_texture *get_texture(gc_scene *scene, char *name)
{
    gc_texture **textures;

    if (!scene) {
        my_printf("No scene, can't load textures\n");
        return (NULL);
    }
    if (!name) {
        my_printf("Texture name: null. How should I find a texture ?\n");
        return (NULL);
    }
    textures = scene->textures;
    if (!textures)
        return (NULL);
    for (int i = 0; textures[i]; i++) {
        if (!my_strcmp(textures[i]->name, name))
            return (textures[i]);
    }
    my_printf("Gamacon: no texture found for the name \"%s\"\n", name);
    return (NULL);
}

void texture_destroy(gc_texture *texture)
{
    sfTexture_destroy(texture->texture);
    free(texture->name);
    free(texture);
}

gc_texture *texture_create(const char *path)
{
    gc_texture *texture = malloc(sizeof(gc_texture));

    if (!texture)
        return (NULL);
    texture->texture = sfTexture_createFromFile(path, NULL);
    texture->name = my_strdup(path);
    if (!texture->texture || !texture->name)
        return (NULL);
    sfTexture_setRepeated(texture->texture, sfTrue);
    texture->destroy = &texture_destroy;
    return (texture);
}