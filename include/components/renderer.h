/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** texture_renderer
*/

#pragma once

#include "component.h"
#include "vector2.h"

typedef enum gc_texturetype {
    GC_TEXTUREREND,
    GC_ANIMREND,
    GC_TXTREND,
    GC_MAP,
    GC_NONE
} gc_texturetype;

typedef enum render_mode {
    RENDER_MODE_NORMAL,
    RENDER_MODE_CENTERED,
    RENDER_MODE_REVERSED
} render_mode;

struct renderer
{
    gc_component base;
    enum gc_texturetype type;
    void *data;
    bool is_visible;
    render_mode render_mode_x;
    render_mode render_mode_y;
    void (*destroy)(struct renderer *);
};

void sprite_ctr(struct renderer *cmp, va_list args);
void sprite_fdctr(gc_scene *scene, struct renderer *cmp, node *n);

void anim_ctr(struct renderer *cmp, va_list args);
void anim_fdctr(gc_scene *scene, struct renderer *cmp, node *n);
void rend_set_anim(struct renderer *rend, const char *name);

void text_ctr(struct renderer *cmp, va_list args);
void text_fdctr(gc_scene *scene, struct renderer *cmp, node *n);

void map_ctr(struct renderer *cmp, va_list args);
void map_fdctr(gc_scene *scene, struct renderer *cmp, gc_entity *entity);

extern const struct renderer renderer_component;