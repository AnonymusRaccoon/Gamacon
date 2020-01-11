/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_music_player
*/

#include "engine.h"
#include <SFML/Audio.h>

void sfml_play_music(void *music)
{
    sfMusic_setLoop(music, true);
    sfMusic_play(music);
}

void sfml_stop_music(gc_engine *engine)
{
    void *music;

    if (!engine->scene)
        return;
    music = engine->scene->get_data(engine->scene, "music", NULL);
    sfMusic_stop(music);
}