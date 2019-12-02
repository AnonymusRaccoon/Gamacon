/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** scene
*/

#pragma once

#include "entity.h"
#include "texture.h"

typedef struct gc_scene
{
    gc_entity *entity_list;
    gc_texture *texture;
} gc_scene;