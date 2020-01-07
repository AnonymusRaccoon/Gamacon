/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** update_to_cam
*/

#include "entity.h"
#include "scene.h"
#include "systems/camerafollow_system.h"
#include "components/transform_component.h"
#include "systems/sfml_renderer_system.h"
#include <SFML/Graphics.h>

void entities_update_to_cam(gc_scene *scene, \
struct sfml_renderer_system *renderer, struct camerafollow_system *cam)
{
    gc_list *list;
    gc_entity *entity;
    sfVector2f size;

    list = scene->get_entity_by_cmp(scene, "fixed_to_cam");
    for (gc_list *li = list; li; li = li->next) {
        entity = (gc_entity *)li->data;
        size = sfView_getSize(renderer->view);
        GETCMP(transform_component)->position = (gc_vector2) {
            cam->cam_pos.x - size.x / 2,
            cam->cam_pos.y + size.y / 2,
        };
    }
}

void entities_update_to_cam_size(gc_scene *scene, gc_vector2 size)
{
    gc_list *list;
    gc_entity *entity;

    list = scene->get_entity_by_cmp(scene, "fixed_to_cam");
    for (gc_list *li = list; li; li = li->next) {
        entity = (gc_entity *)li->data;
        GETCMP(transform_component)->size = (gc_vector2) {
            size.x,
            size.y
        };
    }
}