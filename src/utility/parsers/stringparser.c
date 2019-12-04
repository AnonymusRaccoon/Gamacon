/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** stringparser
*/

#include "utility.h"

char *parse_arg_str(char **str)
{
    char *p = my_strchr(*str, ' ');
    char *tmp = *str;

    if (!p)
        return (*str);
    *p = '\0';
    *str = p + 1;
    return (tmp);
}