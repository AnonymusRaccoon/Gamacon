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
#include "components/vertex_component.h"

gc_data *sfml_music_loader(gc_engine *engine, gc_scene *scene, node *n);
gc_data *sfml_sprite_loader(gc_engine *engine, gc_scene *scene, node *n);
gc_data *sfml_font_loader(gc_engine *engine, gc_scene *scene, node *n);

sfTexture *get_texture(gc_scene *scene, char *name);
sfVertexArray *sfml_init_verticies(void);
sfRenderStates *sfml_init_render_state(void);

void sfmlrenderer_draw_texture(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_entity *entity, gc_sprite *sprite);
void sfmlrenderer_draw_anim(struct sfml_renderer_system *renderer, \
gc_entity *entity, gc_animholder *holder, float dtime);
void sfmlrenderer_draw_txt(gc_engine *engine, \
struct sfml_renderer_system *renderer, struct transform_component *tra, \
gc_text *txt);
void sfmlrenderer_draw_tilemap(struct sfml_renderer_system *this,
struct transform_component *pos, struct vertex_component *txt);

void sfml_texture_destroy(gc_data *data);
void sfml_music_destroy(gc_data *data);
void sfml_font_destroy(gc_data *data);

bool sfml_is_open(gc_engine *engine);
bool sfml_has_focus(gc_engine *engine);
bool sfml_is_keypressed(int key);
void sfml_handle_events(gc_engine *engine);
void sfml_draw(gc_engine *engine);
void sfml_play_music(void *music);
void sfml_stop_music(gc_engine *engine);
void sfml_resize(gc_engine *engine, gc_vector2 size);
gc_vector2 sfml_get_screen_size(gc_engine *engine);
gc_vector2 sfml_engine_get_cursor_pos(gc_engine *engine);

void entities_update_to_cam(gc_scene *scene, \
struct sfml_renderer_system *renderer, struct camerafollow_system *cam);
void entities_update_to_cam_size(gc_scene *scene, gc_vector2 size);
