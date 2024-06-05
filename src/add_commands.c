/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** add information of the commands in the structure
*/

#include "../include/my.h"

int number_params(char **array, int_fast8_t mnemonic)
{
    int prog_size = 0;

    if (mnemonic != 0x01 && mnemonic != 0x09 &&
        mnemonic != 0x0c && mnemonic != 0x0f)
        prog_size++;
    for (int i = 0; array[i] != NULL; i++) {
        if (array[i][0] == 'r')
            prog_size += 1;
        if (array[i][0] == '%' && array[i][1] != ':')
            prog_size += DIR_SIZE;
        if (array[i][0] == '%' && array[i][1] == ':')
            prog_size += IND_SIZE;
        if (array[i][0] != 'r' && array[i][0] != '%')
            prog_size += IND_SIZE;
        if (array[i][0] == '%' && array[i][1] != ':'
        && (mnemonic == 0x0b || mnemonic == 0x03 ||
        mnemonic == 0x09 || mnemonic == 0x0a))
            prog_size = prog_size - 2;
    }
    return prog_size;
}

void add_information(command_t *command, char **array, char *label)
{
    int i = 0;

    command->label = NULL;
    command->mnemonic = mnemonic(array[0]);
    if (label != NULL) {
        change_letters(label, ':', 0);
        command->label = my_strdup(label);
    }
    for (i = 0; i < MAX_ARGS_NUMBER && array[i + 1] != NULL; i++)
        command->args[i] = my_strdup(array[i + 1]);
    command->args[i] = NULL;
    command->next = NULL;
}

void command_add(file_t *file, char **array, char *label)
{
    command_t *prev = NULL;
    command_t *command = malloc(sizeof(command_t));

    add_information(command, array, label);
    if (file->command == NULL) {
        command->offset = 0;
        file->command = command;
        return;
    }
    for (command_t *n = file->command; n != NULL; n = n->next)
        prev = n;
    command->offset = prev->offset +
    number_params(prev->args, prev->mnemonic) + 1;
    prev->next = command;
}

int check_commands(file_t *file)
{
    int prog_size = 0;

    for (command_t *c = file->command; c != NULL; c = c->next) {
        prog_size = c->offset;
        if (c->next == NULL)
            prog_size += number_params(c->args, c->mnemonic) + 1;
    }
    return prog_size;
}

void change_int(char *str, size_t size)
{
    char c = 0;

    for (size_t i = 0; i < size; i++) {
        c = str[size - 1];
        str[size - 1] = str[i];
        str[i] = c;
        size--;
    }
}
