/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_drawer
*/

#include "sfml_renderer.h"
#include "vector2.h"
#include "sprite.h"
#include "text.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include "my.h"
#include <SFML/Graphics.h>

void sfmlrenderer_setorigin(struct sfml_renderer_system *renderer, \
gc_entity *entity, gc_sprite *sprite, struct transform_component *tra)
{
	sfVector2f scale = (sfVector2f){
		tra->size.x * sprite->scale.x / sprite->rect.width,
		tra->size.y * sprite->scale.y / sprite->rect.height
	};

	sfSprite_setScale(renderer->sprite, scale);
	if (entity->has_component(entity, "fixed_to_cam"))
		sfSprite_setOrigin(renderer->sprite, (sfVector2f) {
			sprite->rect.width / 2,
			sprite->rect.height / 2
		});
	else
		sfSprite_setOrigin(renderer->sprite, (sfVector2f){
			scale.x < 0 ? sprite->rect.width : 0,
			scale.y < 0 ? sprite->rect.height : 0
		});
}

void sfmlrenderer_draw_texture(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_entity *entity, gc_sprite *sprite)
{
    sfVector2f pos = (sfVector2f){tra->position.x, -tra->position.y};

    sprite->pos = tra->position;
    if (!sprite->texture) {
		my_printf("Trying to render a sprite without texture.\n");
		return;
	}
    sfSprite_setTexture(renderer->sprite, sprite->texture, true);
    sfSprite_setTextureRect(renderer->sprite, (sfIntRect){
        sprite->rect.left, sprite->rect.top,
        sprite->rect.width, sprite->rect.height
    });
    sfSprite_setPosition(renderer->sprite, pos);
   	sfmlrenderer_setorigin(renderer, entity, sprite, tra);
    sfRenderWindow_drawSprite(renderer->window, renderer->sprite, NULL);
}

void sfmlrenderer_draw_anim(struct sfml_renderer_system *renderer, \
gc_entity *entity, gc_animholder *holder, float dtime)
{
	struct transform_component *tra = GETCMP(entity, transform_component);
    gc_int_rect *rec = &holder->sprite->rect;
    gc_anim *curr = holder->current;

    if (curr)
        holder->timesince_up += dtime;
    if (curr && holder->timesince_up > 1 / curr->frame_rate) {
        rec->left += rec->width;
        holder->timesince_up = 0;
        if (rec->left > curr->rect.left + rec->width * (curr->frame_count - 1))
            rec->left = curr->rect.left;
    }
    sfmlrenderer_draw_texture(renderer, tra, entity, holder->sprite);
}

void sfmlrenderer_draw_txt(struct sfml_renderer_system *renderer, \
struct transform_component *tra, gc_text *txt)
{
	sfFloatRect bounds;

	sfText_setString(renderer->text, txt->text);
    if (!txt->font)
    	my_printf("%s has a font not loaded. Rendering impossible.", txt->font);
    sfText_setFont(renderer->text, txt->font);
    bounds = sfText_getLocalBounds(renderer->text);
    sfText_setColor(renderer->text, *(sfColor*)&txt->color);
    sfText_setPosition(renderer->text, (sfVector2f){
        tra->position.x - bounds.width / 2,
        -tra->position.y - bounds.height
    });
    sfRenderWindow_drawText(renderer->window, renderer->text, NULL);
}