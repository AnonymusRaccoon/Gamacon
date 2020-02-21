/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** scene_music
*/

#include "engine.h"
#include "errors.h"
#include "scene.h"
#include "xml.h"
#include "my.h"
#include "data.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <malloc.h>

void scene_load_data(gc_engine *engine, gc_scene *scene, node *n)
{
    gc_dataloader *loader;
	gc_data *data;

    scene->data = NULL;
    if (!(n = xml_getnode(n, "data")))
        return;
    for (n = n->child; n; n = n->next) {
        loader = engine->get_dataloader(engine, n->name);
        if (!loader) {
        	my_printf(DATALOADER_NOT_FOUND, n->name);
			return;
		}
		data = loader->load(engine, scene, n);
        if (!data) {
			my_printf(DATALOADER_ERROR, xml_getproperty(n, "name"), n->name);
			return;
		}
        scene->data = list_add(scene->data, data);
    }
}

void scene_load_entity(gc_scene *this, gc_engine *engine, node *n)
{
	gc_dataloader *loader = engine->get_dataloader(engine, n->name);
	gc_data *data;

	if (!loader) {
		my_printf(NO_CUSTOM_ENTITY_LOADER, n->name);
		return;
	}
	data = loader->load(engine, this, n);
	for (gc_list *li = (gc_list *)data->custom; li; li = li->next)
		this->add_entity(this, li->data);
}