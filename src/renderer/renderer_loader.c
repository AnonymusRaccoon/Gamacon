/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** renderer_loader
*/

#include "texture.h"
#include "utility.h"
#include <SFML/Graphics.h>

gc_texture *renderer_load_texture(char *path)
{
    gc_texture *texture = malloc(sizeof(gc_texture));

    if (!texture)
        return (NULL);
    texture->texture = sfTexture_createFromFile(path, NULL);
    texture->name = my_strdup(path);
    return (texture);
}