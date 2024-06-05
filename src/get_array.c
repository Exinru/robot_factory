/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT
** File description:
** robot factory
*/

#include "../include/my.h"

int get_file_height(char const *buffer)
{
    int height = 0;

    for (int cont = 0; buffer[cont] != '\0'; cont++)
        if (buffer[cont] == '\n')
            height++;
    return (height);
}

char **get_array(char *filepath, char *buffer)
{
    int x = get_file_height(buffer) + 1;
    FILE *stream = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char **map = malloc(sizeof(char *) * x);
    int cont = 0;

    nread = getline(&line, &len, stream);
    while (nread != -1) {
        map[cont] = my_strdup(line);
        if (map[cont][my_strlen(map[cont]) - 1] == '\n')
            map[cont][my_strlen(map[cont]) - 1] = '\0';
        change_letters(map[cont], '#', 0);
        cont++;
        nread = getline(&line, &len, stream);
    }
    map[cont] = NULL;
    fclose(stream);
    return (map);
}
