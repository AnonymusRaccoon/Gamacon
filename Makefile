##
## EPITECH PROJECT, 2019
## Gamacon
## File description:
## Makefile
##

SRC = src/engine.c \
	src/engine_internal.c \
	src/component.c \
	src/components/movable_component.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = -I ./include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra

NAME = libgamacon.a

CC = gcc

AR = ar rc

all: build

build: $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all build clean fclean