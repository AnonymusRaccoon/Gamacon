/*
** EPITECH PROJECT, 2020
** My3D
** File description:
** keybindings
*/

#ifndef _KEYBINDINGS_H_
#define _KEYBINDINGS_H_

#include <SFML/Window/Keyboard.h>

typedef enum gc_keybindings
{
    ESCAPE = sfKeyEscape,
    SPACE = sfKeySpace,
    KEY_E = sfKeyE
} gc_keybindings;

typedef enum gc_mousekeys
{
    GC_LEFT,
    GC_RIGHT
} gc_mousekeys;

#endif //_KEYBINDINGS_H_
