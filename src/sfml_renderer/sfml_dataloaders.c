/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_dataloaders
*/

#include "data.h"
#include "xml.h"
#include "sfml_renderer.h"
#include "my.h"
#include <malloc.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>

int sfml_music_loader(gc_data *data, node *n)
{
    char *path = xml_getproperty(n, "src");

    if (!path)
        return (-1);
    data->name = path;
    data->custom = sfMusic_createFromFile(path);
    data->destroy = &sfml_music_destroy;
    if (!data->custom)
        return (-1);
    return (0);
}

int sfml_sprite_loader(gc_data *data, node *n)
{
    char *path = xml_getproperty(n, "src");

    if (!path)
        return (-1);
    data->name = path;
    data->custom = sfTexture_createFromFile(path, NULL);
    if (!data->custom || !data->name)
        return (-1);
    sfTexture_setRepeated(data->custom, sfTrue);
    data->destroy = &sfml_texture_destroy;
    return (0);
}

int sfml_font_loader(gc_data *data, node *n)
{
    char *path = xml_getproperty(n, "src");

    if (!path)
        return (-1);
    data->name = path;
    data->custom = sfFont_createFromFile(path);
    if (!data->custom || !data->name)
        return (-1);
    data->destroy = &sfml_font_destroy;
    return (0);
}