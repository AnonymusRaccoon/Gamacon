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
    gc_list *list;
    gc_entity *entity;
    sfVector2f size;
    gc_vector2 offset;
    struct transform_component *tra;

    list = scene->get_entity_by_cmp(scene, "fixed_to_cam");
    for (gc_list *li = list; li; li = li->next) {
        entity = (gc_entity *)li->data;
        tra = GETCMP(transform_component);
        if (!tra)
            continue;
        size = sfView_getSize(renderer->view);
        offset = GETCMP(fixed_to_cam)->offset;
        tra->position = (gc_vector2) {
            cam->cam_pos.x - size.x / 2 + offset.x,
            cam->cam_pos.y + size.y / 2 - offset.y,
        };
    }
}

void entities_update_to_cam_size(gc_scene *scene, gc_vector2 size)
{
    gc_list *list;
    gc_entity *entity;
    struct transform_component *tra;

    list = scene->get_entity_by_cmp(scene, "fixed_to_cam");
    for (gc_list *li = list; li; li = li->next) {
        entity = (gc_entity *)li->data;
        tra = GETCMP(transform_component);
        if (!tra)
            continue;
        tra->size = (gc_vector2) {
            size.x,
            size.y
        };
    }
}