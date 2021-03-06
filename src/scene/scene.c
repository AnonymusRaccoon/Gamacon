/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** scene
*/

#include "engine.h"
#include "entity.h"
#include "utility.h"

gc_list *get_entity_by_cmp(gc_scene *scene, const char *cmp_name)
{
    for (gc_tupple *tup = scene->entities_by_cmp; tup; tup = tup->next) {
        if (!my_strcmp(tup->name, cmp_name))
            return (tup->entities);
    }
    return (NULL);
}

void *scene_get_data(gc_scene *scene, const char *type, const char *name)
{
    gc_data *data;

    if (!scene || !scene->data)
        return (NULL);
    for (gc_list *li = scene->data; li; li = li->next) {
        data = (gc_data *)li->data;
        if (type && my_strcmp(data->type, type))
            continue;
        if (!name || !my_strcmp(data->name, name))
            return (data->custom);
    }
    return (NULL);
}

gc_data *scene_get_data_ptr(gc_scene *this, void *data)
{
    for (gc_list *list = this->data; list; list = list->next) {
        if (((gc_data *)list->data)->custom == data)
            return (list->data);
    }
    return (NULL);
}

callback_t scene_get_callback(gc_scene *this, char *name)
{
    if (!name)
        return (NULL);
    for (gc_list *cal = this->callbacks; cal; cal = cal->next) {
        if (!my_strcmp(((gc_data *)cal->data)->name, name))
            return (((gc_data *)cal->data)->custom);
    }
    return (NULL);
}