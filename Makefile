##
## EPITECH PROJECT, 2019
## Gamacon
## File description:
## Makefile
##

SRC = src/engine/engine.c \
	src/engine/engine_internal.c \
	src/renderer/sfml_functions.c \
	src/renderer/texture_utility.c \
	src/entity/entity.c \
	src/entity/entity_factory.c \
	src/component.c \
	src/components/movable_component.c \
	src/components/transform_component.c \
	src/components/renderer.c \
	src/components/parallax_component.c \
	src/scene/scene.c \
	src/utility/my_strdup.c \
	src/utility/my_strlen.c \
	src/utility/arraylen.c \
	src/utility/tostr.c \
	src/utility/atoi.c \
	src/utility/my_strchr.c \
	src/utility/my_strcmp.c \
	src/utility/pow.c \
	src/utility/read_line.c \
	src/utility/list.c \
	src/utility/tupple.c \
	src/deserializer/deserialize_entity.c \
	src/deserializer/prefab.c \
	src/system.c \
	src/systems/sfml_renderer_system.c \
	src/systems/movable_system.c \
	src/systems/parallax_system.c \
	src/engine/engine_system_builder.c \
	src/engine/engine_component_builder.c

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

dbg: CFLAGS += -g
dbg: re

.PHONY: all build clean fclean