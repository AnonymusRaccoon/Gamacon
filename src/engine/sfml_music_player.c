/*
** EPITECH PROJECT, 2020
** Twac
** File description:
** sfml_music_player
*/

#include "engine.h"
#include "texture.h"
#include <SFML/Audio.h>

void sfml_play_music(gc_music *music)
{
    sfMusic_setLoop(music->music, true);
    sfMusic_play(music->music);
}