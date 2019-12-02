/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** texture
*/

#pragma once

#include <SFML/Graphics.h>

typedef struct gc_texture
{
    char *name;
    sfTexture *texture;
} gc_texture;