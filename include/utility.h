/*
** EPITECH PROJECT, 2019
** MUL_my_runner_2019
** File description:
** utility
*/

#pragma once

char *my_strdup(const char *src);
int my_strlen(const char *str);
int arraylen(const char **array);
char *tostr(int n);
int my_atoi(const char *str);
int my_strcmp(const char *str1, const char *str2);
int my_strncmp(const char *str1, const char *str2, int n);
char *my_strchr(const char *str, char c);
int parse_arg_int(char **str);
float parse_arg_float(char **str);
char *parse_arg_str(char **str);
int my_pow(int nb, int p);