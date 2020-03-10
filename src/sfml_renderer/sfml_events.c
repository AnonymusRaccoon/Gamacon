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
	struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
	sfEvent event;

	while (sfRenderWindow_pollEvent(rend->window, &event)) {
		switch (event.type) {
		case sfEvtClosed:
			sfRenderWindow_close(rend->window);
			break;
		case sfEvtResized:
			engine->on_resize(engine, (gc_vector2){event.size.width, event.size.height});
			break;
		case sfEvtMouseButtonReleased:
			if (event.mouseButton.button == sfMouseLeft)
				engine->trigger_event(engine, "mouse_left_click");
			if (event.mouseButton.button == sfMouseRight)
				engine->trigger_event(engine, "mouse_right_click");
			break;
		case sfEvtKeyReleased:
			engine->trigger_event(engine, "key_pressed", event.key.code);
			break;
		default:
			break;
		}
	}
}

gc_vector2 sfml_engine_get_cursor_pos(gc_engine *engine)
{
	struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
	sfVector2i pos;
	gc_vector2 ret;
	sfVector2f pos2;

	pos = sfMouse_getPosition(rend->window);
	pos2 = sfRenderWindow_mapPixelToCoords(rend->window, pos, rend->view);
	ret.x = pos2.x;
	ret.y = pos2.y;
	ret.y *= -1;
	return (ret);
}

void sfml_resize(gc_engine *engine, gc_vector2 size)
{
	struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);

	sfView_setSize(rend->view, (sfVector2f){
		size.x,
		size.y
	});
	entities_update_to_cam_size(engine->scene, size);
}

gc_vector2 sfml_get_screen_size(gc_engine *engine)
{
	struct sfml_renderer_system *rend = GETSYS(engine, sfml_renderer_system);
	sfVector2u size = sfRenderWindow_getSize(rend->window);

	return (gc_vector2){size.x, size.y};
}