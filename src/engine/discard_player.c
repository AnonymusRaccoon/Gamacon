/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** discard_player
*/

#include "engine.h"

void engine_play_music(void *music)
{
    (void)music;
}

void engine_stop_music(gc_engine *engine)
{
    (void)engine;
}

void engine_on_resize(gc_engine *engine, gc_vector2 size)
{
	(void)engine;
	(void)size;
}
gc_vector2 engine_get_screen_size(gc_engine *this)
{
	(void)this;
	return ((gc_vector2){0, 0});
}
