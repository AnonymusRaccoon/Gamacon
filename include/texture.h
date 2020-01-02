/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** texture
*/

typedef struct gc_texture gc_texture;

#pragma once

#include <SFML/Graphics.h>

struct gc_texture
{
    char *name;
    sfTexture *texture;
    void (*destroy)(gc_texture *texture);
};

gc_texture *get_texture(gc_scene *scene, char *name);
gc_texture *texture_create(const char *path);