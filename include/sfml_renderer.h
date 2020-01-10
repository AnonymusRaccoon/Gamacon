/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_renderer
*/

#pragma once

#include <SFML/Graphics.h>
#include "scene.h"

int sfml_music_loader(gc_data *data, node *n);
int sfml_sprite_loader(gc_data *data, node *n);

sfTexture *get_texture(gc_scene *scene, char *name);

void sfml_texture_destroy(gc_data *data);
void sfml_music_destroy(gc_data *data);