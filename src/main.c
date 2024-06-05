/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** main function
*/

#include "../include/my.h"

int first_encounter(char *str, char letter)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == letter)
            return i;
    }
    return 0;
}

void clean_str(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
    }
}

void free_all(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int transcription(file_t *file)
{
    FILE *fl = fopen(file->filename, "wb");

    fwrite(file->header, sizeof(header_t), 1, fl);
    add_command(file, fl);
    fclose(fl);
    free(file->header);
    return 0;
}

static int error_handling(int ac, char **av)
{
    struct stat file;
    int i = 0;

    if (ac != 2)
        return -1;
    if (stat(av[1], &file) != 0 || file.st_size == 0)
        return -1;
    return 0;
}

int main(int ac, char **av)
{
    file_t *file = malloc(sizeof(file_t));

    if (error_handling(ac, av) == -1)
        return 84;
    else {
        if (parse_information(file, av[1]) != 84) {
            transcription(file);
            return 0;
        }
    }
    return 84;
}
