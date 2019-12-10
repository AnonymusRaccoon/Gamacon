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


gc_texture *get_texture(gc_engine *engine, char *name)
{
    gc_texture **textures;

    if (!engine->scene || !name)
        return (NULL);
    textures = engine->scene->textures;
    for (int i = 0; textures[i]; i++) {
        if (!my_strcmp(textures[i]->name, name))
            return (textures[i]);
    }
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