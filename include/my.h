/*
** EPITECH PROJECT, 2023
** EPITECH PROJECT SETTING UP
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stddef.h>
    #include <sys/wait.h>
    #include <stdint.h>
    #include <dirent.h>
    #include <errno.h>
    #include "op.h"

typedef struct command_info {
    int_fast8_t mnemonic;
    char *args[MAX_ARGS_NUMBER];
    char *label;
    int offset;
    struct command_info *next;
} command_t;

typedef struct file {
    char **file_info;
    char *filename;
    header_t *header;
    command_t *command;
    int status;
    int registros[REG_NUMBER + 1];
} file_t;

int first_encounter(char *str, char letter);
int get_comment(file_t *fl);
char *my_strncpy(char *dest, char const *src, int n);
int my_strcmp(char const *s1, char const *s2);
int my_put_nbr(int nb);
void my_putchar(char c);
void my_putstr(char const *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char **my_str_to_word_array(char const *str, char delim);
void free_all(char **argv);
void clean_str(char *str);
char **get_array(char *filepath, char *buffer);
int get_name(file_t *fl);
int_fast8_t mnemonic(char *str);
int parse_information(file_t *file, char *filepath);
void add_description(file_t *file, FILE *fl);
void add_name(file_t *file, FILE *fl);
void command_add(file_t *file, char **array, char *label);
int check_commands(file_t *file);
void add_command(file_t *file, FILE *fl);
void change_int(char *str, size_t size);
void search_label(file_t *file, char *label, int offset, FILE *fl);
int get_num(char *str);
char *change_letters(char *str, char letter, char which);
char *get_filename(char *filepath);
void write_params(file_t *file, command_t *command, FILE *fl);
int cases(file_t *file, int i);
void *my_calloc(size_t num_elems, size_t elem);
int check_rest(int size, char *str, int opt);
#endif
