/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT
** File description:
** write the commands in the file
*/

#include "../include/my.h"

void write_indirect(char *str, FILE *fl)
{
    int num = get_num(str);
    uint16_t byte = num;

    change_int((char *)&byte, sizeof(uint16_t));
    fwrite(&byte, sizeof(uint16_t), 1, fl);
    return;
}

void write_direct(char *str, FILE *fl)
{
    int num = get_num(str);

    change_int((char *)&num, 4);
    fwrite(&num, sizeof(int), 1, fl);
    return;
}

void write_register(char *str, FILE *fl)
{
    int num = get_num(str);

    fwrite(&num, sizeof(uint8_t), 1, fl);
    return;
}

void write_params(file_t *file, command_t *command, FILE *fl)
{
    int_fast8_t mnemo = command->mnemonic;

    for (int i = 0; command->args[i] != NULL; i++) {
        if (command->args[i][0] == 'r')
            write_register(command->args[i] + 1, fl);
        if (command->args[i][0] == '%' && command->args[i][1] != ':' &&
        (mnemo != 0x0b && mnemo != 0x03 && mnemo != 0x09 && mnemo != 0x0a))
            write_direct(command->args[i] + 1, fl);
        if (command->args[i][0] == '%' && command->args[i][1] == ':') {
            search_label(file, command->args[i] + 2, command->offset, fl);
            continue;
        }
        if (command->args[i][0] == '%' && command->args[i][1] != ':' &&
        (mnemo == 0x0b || mnemo == 0x03 || mnemo == 0x09 || mnemo == 0x0a))
            write_indirect(command->args[i] + 1, fl);
        if (command->args[i][0] != 'r' && command->args[i][0] != '%')
            write_indirect(command->args[i], fl);
    }
}
