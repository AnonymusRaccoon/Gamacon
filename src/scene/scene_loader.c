/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** scene_music
*/

#include "engine.h"
#include "scene.h"
#include "xml.h"
#include "my.h"
#include "data.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <malloc.h>

gc_dataloader *gc_dataloader_from_type(gc_engine *engine, const char *type)
{
    gc_dataloader *loader;

    for (gc_list *li = engine->dataloaders; li; li = li->next) {
        loader = (gc_dataloader *)li->data;
        if (!my_strcmp(loader->type, type))
            return (loader);
    }
    return (NULL);
}

void scene_load_data(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_data *data;
    gc_dataloader *loader;

    scene->data = NULL;
    if (!(n = xml_getnode(n, "data")))
        return;
    for (n = n->child; n; n = n->next) {
        if (!(data = malloc(sizeof(*data))))
            return;
        data->type = my_strdup(n->name);
        data->name = xml_getproperty(n, "name");
        data->destroy = NULL;
        loader = gc_dataloader_from_type(engine, data->type);
        if (!loader)
            return ((void)my_printf("Couldn't find data loader for the type %s\
\n", data->type));
        if (loader->load(data, n) < 0)
            return ((void)my_printf("Error while loading data %s (type %s).\
\n", data->name, data->type));
        scene->data = list_add(scene->data, data);
    }
}