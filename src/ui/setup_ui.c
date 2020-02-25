//
// Created by anonymus-raccoon on 2/21/20.
//

#include "engine.h"
#include "data.h"
#include "xml.h"
#include "my.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "components/fixed_to_cam_component.h"
#include "components/clickable_component.h"
#include "systems/sfml_renderer_system.h"
#include <malloc.h>

gc_entity *new_text(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_entity *entity = entity_create();

	entity->add_component(entity, new_component(&transform_component,
		(gc_vector2){0, 0},
		(gc_vector2){0, 0}));
	entity->add_component(entity, new_component(&renderer_component,
		GC_TXTREND,
		xml_getproperty(n, "text"),
		scene->get_data(scene, "font", NULL)));
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){
		xml_getintprop(n, "x"),
		xml_getintprop(n, "y")
		},
		true, true, false));
	return (entity);
}

gc_entity *background_from_text(gc_engine *engine, gc_scene *scene, node *n, \
gc_text *text)
{
	gc_entity *entity = entity_create();
	struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);
	sfTexture *texture = scene->get_data(scene, "sprite", "button_background");

	if (!renderer)
		return (NULL);
	if (!texture)
		my_printf("No texture defined for the button_background.\n");
	entity->add_component(entity, new_component(&transform_component,
		(gc_vector2){0, 0},
		renderer->get_text_size(renderer, text)));
	entity->add_component(entity, new_component(&renderer_component,
		GC_TEXTUREREND,
		texture,
		(sfIntRect){0, 0, -1, -1}));
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){
		xml_getintprop(n, "x"),
		xml_getintprop(n, "y")
		}, true, true, false));
	return (entity);
}

gc_list *new_button(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_list *entities = NULL;
	gc_text text = (gc_text){
		xml_gettempprop(n, "text"),
		scene->get_data(scene, "font", NULL)
	};
	gc_entity *background = background_from_text(engine, scene, n, &text);

	if (!background)
		return (NULL);
	background->add_component(background, new_component(&clickable_component,
		engine, xml_getproperty(n, "click")));
	LISTADD(entities, background);
	LISTADD(entities, new_text(engine, scene, n));
	return (entities);
}

gc_data *button_make(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_data *data = malloc(sizeof(*data));

	data->name = "button";
	data->type = "ui";
	data->destroy = NULL;
	data->custom = new_button(engine, scene, n);
	return (data);
}

void ui_setup(gc_engine *engine)
{
	engine->add_dataloader(engine, "button", &button_make);
}