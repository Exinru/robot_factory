/*
** EPITECH PROJECT, 2024
** EPITECH PROJECT ROBOT FACTORY
** File description:
** change a string into a words array
*/

/*
** EPITECH PROJECT, 2023
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/
#include "../include/my.h"

int count_words_letter(char const *str, char delim)
{
    int num_letter = 0;
    int spaces = 0;

    while (str[spaces] == delim)
        spaces++;
    for (int i = spaces; str[i] != delim && str[i] != '\0'; i++)
        num_letter++;
    return num_letter;
}

char *add_word_to_str(char const *str, char delim)
{
    int num_letters = count_words_letter(str, delim);
    char *word = malloc(sizeof(char) * (num_letters + 1));
    int spaces = 0;

    while (str[spaces] == ' ')
        spaces++;
    for (int i = spaces; str[i] != delim && str[i] != '\0'; i++)
        word[i] = str[i];
    word[num_letters] = '\0';
    return word;
}

int count_words(char const *str, char delim)
{
    int cont = 1;
    int spaces = 0;

    while (str[spaces] == delim)
        spaces++;
    if (str[spaces] == '\0' || str[spaces] == '\n')
        return 0;
    for (int i = spaces; str[i] != '\0'; i++) {
        if (str[i] == delim && str[i + 1] != delim)
            cont++;
    }
    return (cont);
}

char **my_str_to_word_array(char const *str, char delim)
{
    int num_words = count_words(str, delim);
    char **array = malloc(sizeof(char *) * (num_words + 1));
    int j = 0;

    for (int i = 0; str[i] != 0 && i < my_strlen(str); i++) {
        if (str[i] == delim)
            continue;
        array[j] = add_word_to_str(str + i, delim);
        i = i + my_strlen(array[j]) - 1;
        j++;
    }
    array[j] = NULL;
    return array;
}
