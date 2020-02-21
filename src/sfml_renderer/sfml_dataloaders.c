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

gc_data *sfml_music_loader(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_data *data = malloc(sizeof(*data));

    if (!data)
    	return (NULL);
	data->type = my_strdup(n->name);
	data->name = xml_getproperty(n, "src");
    if (!data->name || !data->type)
        return (NULL);
    data->custom = sfMusic_createFromFile(data->name);
    data->destroy = &sfml_music_destroy;
    if (!data->custom)
        return (NULL);
    return (data);
}

gc_data *sfml_sprite_loader(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_data *data = malloc(sizeof(*data));

	if (!data)
		return (NULL);
	data->type = my_strdup(n->name);
    data->name = xml_getproperty(n, "src");
    if (!data->name || !data->type)
    	return (NULL);
    data->custom = sfTexture_createFromFile(data->name, NULL);
    if (!data->custom)
        return (NULL);
    sfTexture_setRepeated(data->custom, sfTrue);
    data->destroy = &sfml_texture_destroy;
	if (xml_hasproperty(n, "name"))
		data->name = xml_getproperty(n, "name");
    return (data);
}

gc_data *sfml_font_loader(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_data *data = malloc(sizeof(*data));

	if (!data)
		return (NULL);
	data->type = my_strdup(n->name);
    data->name = xml_getproperty(n, "src");
    if (!data->name || !data->type)
    	return (NULL);
    data->custom = sfFont_createFromFile(data->name);
    if (!data->custom)
        return (NULL);
    data->destroy = &sfml_font_destroy;
    return (data);
}