/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** renderer_loader
*/

#include "texture.h"
#include "utility.h"
#include <SFML/Graphics.h>
#include <stdlib.h>


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
    texture->destroy = &texture_destroy;
    return (texture);
}