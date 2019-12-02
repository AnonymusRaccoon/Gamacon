/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** texture
*/

#pragma once

#include <SFML/Graphics.h>

typedef struct gcTexture
{
    char *name;
    sfTexture *texture;
} gcTexture;