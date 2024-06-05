##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## makefile
##

CC=gcc

CFLAGS= -Wall -Wextra -g

SRC = 	src/str_to_word_array.c \
	src/main.c	\
	src/name.c	\
	src/lib.c \
	src/lib2.c \
	src/command.c \
	src/parse.c \
	src/get_array.c \
	src/add_commands.c \
	src/write.c \
	src/cases.c

O_FILES = $(SRC:.c=.o)

NAME = asm

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(O_FILES)

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
