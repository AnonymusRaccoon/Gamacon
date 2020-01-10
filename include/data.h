/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** data
*/

#pragma once

#include "xml.h"

typedef struct gc_data gc_data;
struct gc_data
{
    char *type;
    char *name;
    void *custom;
    void (*destroy)(gc_data *data);
};

typedef int (*gc_loader)(gc_data *data, node *n);

typedef struct gc_dataloader
{
    char *type;
    gc_loader load;
} gc_dataloader;