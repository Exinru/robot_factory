/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** main function
*/

#include "../include/my.h"

int get_comment(file_t *fl)
{
    char **array = NULL;
    int j = 0;
    int i = 0;
    int z = 0;

    for (i = 0; fl->file_info[i] != NULL; i++) {
        array = my_str_to_word_array(fl->file_info[i], ' ');
        if (array[0] != NULL && my_strcmp(array[0], COMMENT_CMD_STRING) == 0)
            break;
        free_all(array);
        array = NULL;
    }
    if (array == NULL || array[1] == NULL || array[1][0] != '"')
        return 84;
    for (z = first_encounter(fl->file_info[i], '"') + 1;
        fl->file_info[i][z] != '"'; z++) {
        fl->header->comment[j] = fl->file_info[i][z];
        j++;
    }
    return check_rest(j, fl->file_info[i] + z, 1);
}

static char *get_file_content(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    struct stat file_info;
    char *buffer = NULL;

    if (stat(filepath, &file_info) == -1)
        return NULL;
    buffer = (char *)malloc(sizeof(char) * (file_info.st_size + 1));
    read(fd, buffer, file_info.st_size);
    buffer[file_info.st_size] = '\0';
    close(fd);
    return buffer;
}

int get_prog_size(file_t *file)
{
    char **array = NULL;
    int sp_case = -1;

    for (int i = 0; file->file_info[i] != NULL; i++) {
        change_letters(file->file_info[i], ',', ' ');
        sp_case = cases(file, i);
        if (sp_case != -1) {
            i = i + ((sp_case == 0) ? 0 : 1);
            continue;
        }
        array = my_str_to_word_array(file->file_info[i], ' ');
        if (mnemonic(array[0]) == -1 && mnemonic(array[1]) != -1) {
            command_add(file, array + 1, array[0]);
        } else
            command_add(file, array, NULL);
        free_all(array);
    }
    file->header->prog_size = check_commands(file);
    return 0;
}

int add_header(file_t *file)
{
    file->header = (header_t *)my_calloc(1, sizeof(header_t));
    file->header->prog_size = 0;
    file->header->magic = 0xf383ea00;
    if (get_name(file) == 84)
        return 84;
    if (get_comment(file) == 84)
        return 84;
    if (get_prog_size(file) == 84)
        return 84;
    return 0;
}

int parse_information(file_t *file, char *filepath)
{
    char *copy_filepath = my_strdup(filepath);
    char *buffer = get_file_content(copy_filepath);

    file->command = NULL;
    file->status = 0;
    file->file_info = get_array(copy_filepath, buffer);
    for (int i = 0; file->file_info[i] != NULL; i++)
        clean_str(file->file_info[i]);
    file->filename = get_filename(copy_filepath);
    file->status = add_header(file);
    change_int((char *)&file->header->prog_size, 4);
    free(copy_filepath);
    free(buffer);
    return file->status;
}
