/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** scene
*/

#pragma once

#include "entity.h"
#include "texture.h"

typedef struct gcScene
{
    Entity *entity_list;
    gcTexture *texture;
} gcScene;