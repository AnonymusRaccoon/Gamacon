/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** utility
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

char *my_strdup(const char *src);
int my_printf(const char *fmt, ...);
int my_strlen(const char *str);
int arraylen(const bool *array);
char *tostr(int n);
int my_atoi(const char *str);
int my_strcmp(const char *str1, const char *str2);
int my_strncmp(const char *str1, const char *str2, int n);
char *my_strchr(const char *str, char c);
int parse_arg_int(char **str);
float parse_arg_float(char **str);
char *parse_arg_str(char **str);
int my_pow(int nb, int p);
int my_sqrt(int nb);
void *my_realloc(void *oldptr, size_t oldsize, size_t newsize);

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) ((x) > 0 ? (x) : -(x))

#define CLAMP(x, min, max) \
((((x) > (max) ? (max) : (x)) < (min)) ? (min) : ((x) > (max) ? (max) : (x)))

#define MY_OVERFLOW(x, value) (x = ((x) > (value) ? -(value) : (x)))
#define MY_UNDERFLOW(x, value) (x = ((x) < (value) ? -(value) : (x)))
