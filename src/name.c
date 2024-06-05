/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** main function
*/
#include "../include/my.h"

int check_rest(int size, char *str, int opt)
{
    int start = 0;

    if (size > PROG_NAME_LENGTH && opt == 0)
        return 84;
    if (size > COMMENT_LENGTH && opt == 1)
        return 84;
    if (str[0] == '\0')
        return 84;
    if (str[0] == '"')
        start++;
    for (int i = start; str[i] != '\0'; i++)
        if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
            return 84;
    return 0;
}

int get_name(file_t *fl)
{
    char **array = NULL;
    int j = 0;
    int i = 0;
    int z = 0;

    for (i = 0; fl->file_info[i] != NULL; i++) {
        array = my_str_to_word_array(fl->file_info[i], ' ');
        if (array[0] != NULL && my_strcmp(array[0], NAME_CMD_STRING) == 0)
            break;
        free_all(array);
        array = NULL;
    }
    if (array == NULL || array[1] == NULL || array[1][0] != '"')
        return 84;
    for (z = first_encounter(fl->file_info[i], '"') + 1;
        fl->file_info[i][z] != '"' && fl->file_info[i][z] != '\0'; z++) {
        fl->header->prog_name[j] = fl->file_info[i][z];
        j++;
    }
    return check_rest(j, fl->file_info[i] + z, 0);
}

char *change_letters(char *str, char letter, char which)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == letter)
            str[i] = which;
    return str;
}

char *get_filename(char *filepath)
{
    char **paths = my_str_to_word_array(filepath, '/');
    int i = 0;
    char *filename = NULL;

    while (paths[i] != NULL)
        i++;
    filename = malloc(sizeof(char) * (my_strlen(paths[i - 1]) + 4));
    my_strncpy(filename, paths[i - 1], my_strlen(paths[i - 1]) - 1);
    my_strcpy(filename + my_strlen(paths[i - 1]) - 1, "cor");
    filename[my_strlen(paths[i - 1]) + 3] = '\0';
    return filename;
}
