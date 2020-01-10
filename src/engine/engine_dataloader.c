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

void engine_add_dataloader(gc_engine *engine, char *type, gc_loader loader)
{
    gc_dataloader *dataloader = malloc(sizeof(*dataloader));

    if (!dataloader)
        return ((void)my_printf("Couldn't malloc dataloader for %s\n", type));
    dataloader->type = type;
    dataloader->load = loader;
    engine->dataloaders = list_add(engine->dataloaders, dataloader);
}