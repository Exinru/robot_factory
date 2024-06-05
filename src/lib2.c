/*
** EPITECH PROJECT, 2023
** EPITECH PROJECT TEK1
** File description:
** c library
*/

#include "../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    size_t i = 0;

    while (s1[i] == s2[i]){
        if (s1[i] == 0)
            break;
        i ++;
    }
    return (s1[i] - s2[i]);
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int cont = 0;

    while (cont < n) {
        dest[cont] = src[cont];
        if (src[cont] == '\0') {
            break;
        }
        cont = cont + 1;
    }
    return (dest);
}

char *my_strcpy(char *dest, char const *src)
{
    int cont = 0;

    while (src[cont] != '\0') {
        dest[cont] = src[cont];
        cont++;
    }
    dest[cont] = '\0';
    return (dest);
}

char *my_strdup(char const *src)
{
    int letters = my_strlen(src);
    char *new_string = (char *)malloc(sizeof(char) * (letters + 1));

    if (new_string == NULL)
        return NULL;
    for (int i = 0; src[i] != '\0'; i++)
        new_string[i] = src[i];
    new_string[letters] = '\0';
    return (new_string);
}

void *my_calloc(size_t num_elems, size_t elem)
{
    size_t space = num_elems * elem;
    char *str = malloc(space);

    if (str == NULL)
        return NULL;
    for (size_t i = 0; i < space; i++)
        str[i] = 0;
    return str;
}
