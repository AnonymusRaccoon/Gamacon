/*
** EPITECH PROJECT, 2019
** Get the first number in the string
** File description:
** firstnbr
*/

#include "utility.h"

long get_nbr(char **str, int length)
{
    char c = (*str)[0];
    long n = 0;

    if (c >= '0' || c <= '9')
        n += (c - '0') * my_pow(10, length - 1);
    *str = *str + 1;
    if (length == 1)
        return (n);
    return (n + get_nbr(str, length - 1));
}

int parse_end(char **str, int strlen, int start, int mult)
{
    long nbr;

    if (strlen > 12 || strlen == 0)
        return (0);
    *str = *str + start;
    nbr = get_nbr(str, strlen) * mult;
    if (nbr > 2147483647 || nbr < -2147483648)
        return (0);
    return (nbr);
}

int parse_int(char **str)
{
    int strlen = 0;
    int start = -1;
    int mult = 1;

    for (int i = 0; (*str)[i]; i++) {
        if ((*str)[i] >= '0' && (*str)[i] <= '9') {
            start = start == -1 ? 0 : start;
            strlen++;
            continue;
        }
        if (start == -1 && \
((*str)[i] == ' ' || (*str)[i] == '+' || (*str)[i] == '-')) {
            start++;
            mult = (*str)[i] == '-' ? -1 : 1;
            continue;
        }
        break;
    }
    return (parse_end(str, strlen, start, mult));
}