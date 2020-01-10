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