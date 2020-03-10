//
// Created by anonymus-raccoon on 2/21/20.
//

#include "engine.h"
#include "data.h"
#include "xml.h"
#include "sprite.h"
#include "my.h"
#include "components/transform_component.h"
#include "components/renderer.h"
#include "components/fixed_to_cam_component.h"
#include "components/clickable_component.h"
#include "systems/sfml_renderer_system.h"
#include "ui.h"
#include <malloc.h>
#include "components/tag_component.h"
#include "components/input_component.h"

gc_entity *background_from_text(gc_engine *engine, gc_scene *scene, node *n, \
gc_text *text)
{
	gc_entity *entity = entity_create();
	struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
	char *texture_name = xml_gettmpstring(n, "sprite", "button_background");
	sfTexture *texture = scene->get_data(scene, "sprite", texture_name);
	gc_vector2i s = {xml_getintprop(n, "width"), xml_getintprop(n, "height")};
	gc_vector2 ts;

	if (!rend)
		return (NULL);
	ts = rend->get_text_size(rend, text);
	if (!texture)
		my_printf("No texture defined for the button_background.\n");
	entity->add_component(entity, new_component(&transform_component,
		(gc_vector2){0, 0}, (gc_vector2){s.x ? s.x : ts.x, s.y ? s.y : ts.y}));
	entity->add_component(entity, new_component(&renderer_component,
		GC_TEXTUREREND, texture, (gc_int_rect){-1, -1, 0, 0}));
	entity->add_component(entity, new_component(&fixed_to_cam,
		(gc_vector2){xml_getintprop(n, "x"),xml_getintprop(n, "y")},
		true, true, s.x, s.y,
		xml_propcontains(n, "width", "%"), xml_propcontains(n, "height", "%")));
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
	if (xml_hasproperty(n, "background_id"))
		background->id = xml_getintprop(n, "background_id");
	if (xml_getbool(n, "input", false))
		background->add_component(background, new_component(&input_component));
	background->add_component(background, new_component(&clickable_component,
		scene, xml_getproperty(n, "click")));
	if (xml_hasproperty(n, "tag"))
		background->add_component(background, new_component(&tag_component,
			xml_getproperty(n, "tag")));
	if (xml_hasproperty(n, "tooltip"))
		LISTADD(entities, tooltip_make(engine, scene, n, background));
	LISTADD(entities, background);
	LISTADD(entities, new_text(engine, scene, n));
	return (entities);
}

gc_data *button_make(gc_engine *engine, gc_scene *scene, node *n)
{
	gc_data *data = malloc(sizeof(*data));
	gc_list *list = new_button(engine, scene, n);

	data->name = "button";
	data->type = "ui";
	data->destroy = NULL;
	data->custom = list;
	return (data);
}