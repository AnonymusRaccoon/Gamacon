/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** arraylen
*/

#include <stdbool.h>

int arraylen(const bool *array)
{
    int i = 0;

    while (array[i])
        i++;
    return (i);
}