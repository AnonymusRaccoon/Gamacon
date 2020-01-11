/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** scene_destroy
*/

#include "scene.h"
#include "data.h"
#include "list.h"
#include "tupple.h"
#include <malloc.h>

static void free_data(gc_scene *scene)
{
    void *next = NULL;

    for (gc_list *data = scene->data; data; data = next) {
        next = data->next;
        if (((gc_data *)data->data)->destroy)
            ((gc_data *)data->data)->destroy(data->data);
        free(((gc_data *)data->data)->type);
        free(data->data);
        free(data);
    }
}

void scene_destroy(gc_scene *scene)
{
    void *next = NULL;
    gc_tupple *tup = scene->entities_by_cmp;

    for (gc_list *entity = scene->entities; entity; entity = next) {
        next = entity->next;
        ((gc_entity *)entity->data)->destroy(entity->data);
        free(entity);
    }
    free_data(scene);
    for (gc_tupple *tupple = tup; tupple; tupple = tup) {
        tup = tupple->next;
        for (gc_list *li = tupple->entities; li; li = next) {
            next = li->next;
            free(li);
        }
        free(tupple->name);
        free(tupple);
    }
    free(scene);
}