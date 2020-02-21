/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** data
*/

#include "engine.h"

typedef struct gc_data gc_data;
typedef gc_data *(*gc_loader)(gc_engine *engine, gc_scene *scene, node *n);

#ifndef DATA
#define DATA

#include "xml.h"

struct gc_data
{
    char *type;
    char *name;
    void *custom;
    void (*destroy)(gc_data *data);
};

typedef struct gc_dataloader
{
    char *type;
    gc_loader load;
} gc_dataloader;

#endif