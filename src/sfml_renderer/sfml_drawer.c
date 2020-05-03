/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_drawer
*/

#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "systems/sfml_renderer_system.h"
#include "my.h"
#include <SFML/Graphics.h>
#include <utility.h>

void sfmlrenderer_setorigin(struct sfml_renderer_system *renderer, \
gc_entity *entity, gc_sprite *sprite, struct transform_component *tra)
{
    sfVector2f scale = (sfVector2f){
        tra->size.x * sprite->scale.x / sprite->rect.width,
        tra->size.y * sprite->scale.y / sprite->rect.height
    };
    struct renderer *rend = GETCMP(entity, renderer);
    int ori_x = scale.x < 0 ? sprite->rect.width : 0;
    int ori_y = scale.y < 0 ? sprite->rect.height : 0;

    sfSprite_setScale(renderer->sprite, scale);
    if (rend->render_mode_x == RENDER_MODE_CENTERED)
        ori_x = sprite->rect.width / 2;
    if (rend->render_mode_y == RENDER_MODE_CENTERED)
        ori_y = sprite->rect.height / 2;
    if (rend->render_mode_x == RENDER_MODE_REVERSED)
        ori_x = ori_x == 0 ? sprite->rect.width : 0;
    if (rend->render_mode_y == RENDER_MODE_REVERSED)
        ori_y = ori_y == 0 ? sprite->rect.height : 0;
    sfSprite_setOrigin(renderer->sprite, (sfVector2f){ori_x, ori_y});
}

void sfmlrenderer_draw_texture(gc_engine *engine, gc_entity *entity, \
gc_sprite *sprite, float dt)
{
    struct transform_component *tra = GETCMP(entity, transform_component);
    sfVector2f pos = (sfVector2f){tra->position.x, -tra->position.y};
    struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

    sprite->pos = tra->position;
    if (!sprite->texture) {
        my_printf("Trying to render a sprite without texture.\n");
        return;
    }
    sfSprite_setTexture(rend->sprite, sprite->texture, true);
    sfSprite_setTextureRect(rend->sprite, (sfIntRect){
        sprite->rect.left, sprite->rect.top,
        sprite->rect.width, sprite->rect.height
    });
    sfSprite_setPosition(rend->sprite, pos);
    sfmlrenderer_setorigin(rend, entity, sprite, tra);
    sfRenderWindow_drawSprite(rend->window, rend->sprite, NULL);
}

void sfmlrenderer_draw_anim(gc_engine *engine, gc_entity *entity, \
gc_animholder *holder, float dtime)
{
    gc_int_rect *rec = &holder->sprite->rect;
    gc_anim *curr = holder->current;

    if (curr)
        holder->timesince_up += dtime;
    if (curr && holder->timesince_up > 1 / curr->frame_rate) {
        rec->left += rec->width;
        holder->timesince_up = 0;
        if (rec->left >= curr->rect.left + rec->width * (curr->frame_count - 1))
            rec->left = curr->rect.left;
    }
    sfmlrenderer_draw_texture(engine, entity, holder->sprite, dtime);
}

void sfmlrenderer_settxtpos(sfText *txt, gc_entity *entity, sfFloatRect bounds)
{
    struct renderer *rend = GETCMP(entity, renderer);
    struct transform_component *tra = GETCMP(entity, transform_component);
    int ori_x = 0;
    int ori_y = rend->render_mode_y == RENDER_MODE_REVERSED ? 0 : bounds.height;

    if (rend->render_mode_x == RENDER_MODE_CENTERED)
        ori_x = bounds.width / 2;
    if (rend->render_mode_y == RENDER_MODE_CENTERED)
        ori_y = bounds.height / 2;
    sfText_setPosition(txt, (sfVector2f) {
        tra->position.x,
        -tra->position.y
    });
    sfText_setOrigin(txt, (sfVector2f){ori_x, ori_y});
}

void sfmlrenderer_draw_txt(gc_engine *engine, gc_entity *entity, \
gc_text *txt, float dt)
{
    struct sfml_renderer_system *this = GETSYS(engine, sfml_renderer_system);
    struct transform_component *tra = GETCMP(entity, transform_component);
    sfFloatRect bounds;
    float size = 1;
    gc_vector2 screen_size = engine->get_screen_size(engine);

    if (txt->resize)
        size = 1 / MAX(800 / screen_size.x, 600 / screen_size.y);
    sfText_setString(this->text, txt->text);
    if (!txt->font)
        my_printf("%s has a font not loaded. Rendering impossible.", txt->font);
    sfText_setFont(this->text, txt->font);
    sfText_setCharacterSize(this->text, txt->size * size);
    bounds = sfText_getLocalBounds(this->text);
    tra->size.x = bounds.width;
    tra->size.y = bounds.height;
    sfText_setColor(this->text, *(sfColor*)&txt->color);
    sfmlrenderer_settxtpos(this->text, entity, bounds);
    sfRenderWindow_drawText(this->window, this->text, NULL);
}