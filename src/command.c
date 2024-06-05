/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** main function
*/

#include "../include/my.h"

int get_num(char *str)
{
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] <= '9' && str[i] >= '0')
            num = (num * 10) + (str[i] - 48);
    return num;
}

int_fast8_t tp_args(char *str)
{
    if (str[0] == 'r')
        return 0b01;
    if (str[0] == '%')
        return 0b10;
    return 0b11;
}

void search_label(file_t *file, char *label, int offset, FILE *fl)
{
    unsigned int num = 0;
    uint16_t byte = 0;

    for (command_t *c = file->command; c != NULL; c = c->next) {
        if (c->label == NULL)
            continue;
        if (my_strcmp(c->label, label) == 0) {
            num = c->offset - offset;
            byte = num;
            change_int((char *)&byte, sizeof(uint16_t));
            fwrite(&byte, sizeof(uint16_t), 1, fl);
            return;
        }
    }
    return;
}

static void add_coding_byte(command_t *command, FILE *fl)
{
    char c = 0;
    int i = 0;

    for (i = 0; i < 4 && command->args[i] != NULL; i++) {
        c = (c << 2) + tp_args(command->args[i]);
    }
    for (i = i; i < 4; i++)
        c = (c << 2) + 0b00;
    fwrite(&c, sizeof(char), 1, fl);
}

void add_command(file_t *file, FILE *fl)
{
    for (command_t *c = file->command; c != NULL; c = c->next) {
        fwrite(&c->mnemonic, sizeof(int_fast8_t), 1, fl);
        if (c->mnemonic != 0x01 && c->mnemonic != 0x09 &&
        c->mnemonic != 0x0c && c->mnemonic != 0x0f)
            add_coding_byte(c, fl);
        write_params(file, c, fl);
    }
}

int_fast8_t mnemonic(char *str)
{
    char *options[17] = {"live", "ld", "st", "add", "sub",
        "and", "or", "xor", "zjmp", "ldi", "sti", "fork",
        "lld", "lldi", "lfork", "aff", NULL};
    int_fast8_t mnemonic[] = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
    0x0e, 0x0f, 0x10};

    if (str == NULL)
        return -1;
    for (int i = 0; options[i] != NULL && i < 17; i++) {
        if (my_strcmp(str, options[i]) == 0) {
            return mnemonic[i];
        }
    }
    return -1;
}
