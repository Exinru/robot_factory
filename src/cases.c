/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** special cases while adding commands
*/

#include "../include/my.h"

int add_label_case(file_t *file, int i, char **array)
{
    char *label = NULL;
    int cont = 0;

    label = my_strdup(array[0]);
    free_all(array);
    for (cont = i; file->file_info[cont + 1] != NULL; cont++) {
        array = my_str_to_word_array(file->file_info[cont + 1], ' ');
        if (mnemonic(array[0]) != -1)
            break;
        free_all(array);
    }
    command_add(file, array, label);
    free(label);
    return cont;
}

int cases(file_t *file, int i)
{
    char **array = NULL;

    array = my_str_to_word_array(file->file_info[i], ' ');
    if (array[0] == NULL || my_strcmp(array[0], NAME_CMD_STRING) == 0 ||
        my_strcmp(array[0], COMMENT_CMD_STRING) == 0) {
        free_all(array);
        return 0;
    }
    if (mnemonic(array[0]) == -1 && array[1] == NULL) {
        return add_label_case(file, i, array);
    }
    free_all(array);
    return -1;
}
