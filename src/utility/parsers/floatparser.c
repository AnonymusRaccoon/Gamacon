/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** floatparser
*/

#include "utility.h"

int get_int_size(int n)
{
    int base_size = my_strlen("0123456789");
    int i = 1;

    while (n >= base_size) {
        n /= base_size;
        i++;
    }
    return (i);
}

float parse_arg_float(char **str)
{
    int i = parse_arg_int(str);
    int decimal = 0;

    if ((*str)[-1] == '.') {
        decimal = parse_arg_int(str);
        return i + ((float)decimal / (get_int_size(decimal) * 10));
    }
    return ((float)i);
}