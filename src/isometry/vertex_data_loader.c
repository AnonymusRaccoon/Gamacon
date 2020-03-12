/*
** EPITECH PROJECT, 2019
** Gamacon
** File description:
** data_loader
*/

#include "engine.h"
#include "data.h"
#include "xml.h"
#include "my.h"
#include <malloc.h>

void vertex_data_destroy(gc_data *data)
{
    free(data->custom);
}

gc_data *tile_texture_array_loader(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_data *data = malloc(sizeof(*data));
    void **arr;
    int count = 0;

    if (!data)
        return (NULL);
    data->type = my_strdup(n->name);
    data->name = NULL;
    if (!data->type)
        return (NULL);
    count = xml_getchildcount(n);
    arr = malloc(sizeof(void *) * (count + 1));
    if (!arr)
        return (NULL);
    n = n->child;
    for (int i = 0; n; n = n->next, i++)
        arr[i] = scene->get_data(scene, "sprite", xml_gettempprop(n, "name"));
    arr[count - 1] = NULL;
    data->custom = arr;
    data->destroy = &vertex_data_destroy;
    return (data);
}