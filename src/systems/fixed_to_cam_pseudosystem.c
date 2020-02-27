/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** update_to_cam
*/

#include "entity.h"
#include "scene.h"
#include "systems/camerafollow_system.h"
#include "component.h"
#include "components/transform_component.h"
#include "components/fixed_to_cam_component.h"
#include "systems/sfml_renderer_system.h"
#include "my.h"
#include <SFML/Graphics.h>

void entities_update_to_cam(gc_scene *scene, \
struct sfml_renderer_system *renderer, struct camerafollow_system *cam)
{
    gc_list *list = scene->get_entity_by_cmp(scene, "fixed_to_cam");

    for (gc_list *li = list; li; li = li->next) {
		gc_entity *entity = (gc_entity *)li->data;
		struct transform_component *tra = GETCMP(entity, transform_component);
		struct fixed_to_cam *fc = GETCMP(entity, fixed_to_cam);
		sfVector2f size = sfView_getSize(renderer->view);
		float x = (cam->cam_pos.x - size.x / 2);
		float y = (cam->cam_pos.y + size.y / 2);

		if (!tra)
			continue;
		x += fc->pos.x * (fc->per_x ? size.x / 100 : 1);
		y -= fc->pos.y * (fc->per_y ? size.y / 100 : 1);
        tra->position = (gc_vector2){x, y};
    }
}

void entities_update_to_cam_size(gc_scene *scene, gc_vector2 size)
{
    gc_list *list;
    gc_entity *entity;
    struct transform_component *tra;
    struct fixed_to_cam *fc;

    list = scene->get_entity_by_cmp(scene, "fixed_to_cam");
    for (gc_list *li = list; li; li = li->next) {
        entity = (gc_entity *)li->data;
        tra = GETCMP(entity, transform_component);
        fc = GETCMP(entity, fixed_to_cam);
        if (!tra)
            continue;
        tra->size = (gc_vector2) {
            fc->per_w != 0 ? size.x * fc->size_x / 100 : tra->size.x,
			fc->per_h != 0 ? size.y * fc->size_y / 100 : tra->size.y
        };
    }
}