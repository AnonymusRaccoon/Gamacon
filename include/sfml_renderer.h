/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_renderer
*/

#pragma once

#include <SFML/Graphics.h>
#include "scene.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"

int sfml_music_loader(gc_data *data, node *n);
int sfml_sprite_loader(gc_data *data, node *n);
int sfml_font_loader(gc_data *data, node *n);

sfTexture *get_texture(gc_scene *scene, char *name);

void sfmlrenderer_draw_texture(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_sprite *sprite);
void sfmlrenderer_draw_anim(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_animholder *holder, float dtime);
void sfmlrenderer_draw_txt(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_text *txt);

void sfml_texture_destroy(gc_data *data);
void sfml_music_destroy(gc_data *data);
void sfml_font_destroy(gc_data *data);