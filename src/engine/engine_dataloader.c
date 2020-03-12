/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** engine_dataloader
*/

#include "engine.h"
#include "data.h"
#include "my.h"
#include <malloc.h>
#include "ui.h"
#include "vertex_data_loader.h"

void engine_add_dataloader(gc_engine *engine, char *type, gc_loader loader)
{
    gc_dataloader *dataloader = malloc(sizeof(*dataloader));

    if (!dataloader)
        return ((void)my_printf("Couldn't malloc dataloader for %s\n", type));
    dataloader->type = type;
    dataloader->load = loader;
    engine->dataloaders = list_add(engine->dataloaders, dataloader);
}

gc_dataloader *engine_get_dataloader(gc_engine *this, const char *type)
{
    gc_dataloader *loader;

    for (gc_list *li = this->dataloaders; li; li = li->next) {
        loader = (gc_dataloader *)li->data;
        if (!my_strcmp(loader->type, type))
            return (loader);
    }
    return (NULL);
}

void engine_init_dataloaders(gc_engine *this)
{
    this->callbacks = NULL;
    this->dataloaders = NULL;
    this->add_dataloader = &engine_add_dataloader;
    this->get_dataloader = &engine_get_dataloader;
    this->add_callback = &engine_add_callback;
    this->add_dataloader(this, "tiles", &tile_texture_array_loader);
    ui_setup(this);
}

void engine_add_callback(gc_engine *this, char *name, callback_t func)
{
    gc_data *callback = malloc(sizeof(*callback));

    if (!this || !callback)
        return;
    callback->type = my_strdup("callback");
    callback->name = name;
    callback->destroy = NULL;
    callback->custom = func;
    LISTADD(this->callbacks, callback);
    if (this->scene)
        this->scene->callbacks = this->callbacks;
}