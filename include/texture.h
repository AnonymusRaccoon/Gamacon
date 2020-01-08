/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** texture
*/

typedef struct gc_texture gc_texture;
typedef struct gc_music gc_music;

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "scene.h"

struct gc_texture
{
    char *name;
    sfTexture *texture;
    void (*destroy)(gc_texture *texture);
};

struct gc_music
{
    sfMusic *music;
};

gc_texture *get_texture(gc_scene *scene, char *name);
gc_texture *texture_create(const char *path);