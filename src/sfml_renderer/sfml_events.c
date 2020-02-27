//
// Created by anonymus-raccoon on 2/27/20.
//

#include "engine.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "sfml_renderer.h"
#include "systems/sfml_renderer_system.h"
#include "systems/camerafollow_system.h"
#include "components/clickable_component.h"
#include "components/transform_component.h"

void sfml_handle_events(gc_engine *engine)
{
	struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);
	sfEvent event;
	sfVector2i mousePos;
	sfVector2f pos;

	while (sfRenderWindow_pollEvent(renderer->window, &event)) {
		if (event.type == sfEvtClosed)
			sfRenderWindow_close(renderer->window);
		if (event.type == sfEvtResized)
			engine->on_resize(engine, (gc_vector2)
			{
				event.size.width,
				event.size.height
			});
		if (event.type == sfEvtMouseButtonReleased) {
			mousePos = sfMouse_getPosition(renderer->window);
			pos = sfRenderWindow_mapPixelToCoords(renderer->window, mousePos, renderer->view);
			pos.y *= -1;
			clickable_onclick(engine, (gc_vector2){pos.x, pos.y});
		}
	}
}

void sfml_resize(gc_engine *engine, gc_vector2 size)
{
	struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);

	sfView_setSize(renderer->view, (sfVector2f){
		size.x,
		size.y
	});
	entities_update_to_cam_size(engine->scene, size);
}

gc_vector2 sfml_get_screen_size(gc_engine *engine)
{
	struct sfml_renderer_system *renderer = GETSYS(sfml_renderer_system);
	sfVector2u size = sfRenderWindow_getSize(renderer->window);

	return (gc_vector2){size.x, size.y};
}