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
	src/components/controllable_component.c \
	src/scene/scene.c \
	src/utility/arraylen.c \
	src/utility/list.c \
	src/utility/tupple.c \
	src/deserializer/deserialize_entity.c \
	src/deserializer/prefab.c \
	src/system.c \
	src/systems/sfml_renderer_system.c \
	src/systems/movable_system.c \
	src/systems/parallax_system.c \
	src/systems/controllable_system.c \
	src/engine/engine_system_builder.c \
	src/engine/engine_component_builder.c

OBJ = $(SRC:%.c=%.o)

TESTS = tests/deserializations.c \
	tests/game_loop.c

INCLUDE = -I ./include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra

LDFLAGS = -L ../my -L ../xmlparser -L ../quadtree\
-lxmlparser -lquadtree -lmy -lcsfml-system -lcsfml-graphics -lcsfml-window

COVERAGE = --coverage -lcriterion

NAME = libgamacon.a

UT = ./ut

CC = gcc

AR = ar rc

all: build

build: $(OBJ)
	$(AR) $(NAME) $(OBJ)

tests_run:
	$(CC) -o $(UT) $(SRC) $(TESTS) $(COVERAGE) $(CFLAGS) $(LDFLAGS)
	$(UT)

clean:
	$(RM) $(OBJ)
	$(RM) *.gc*

fclean: clean
	$(RM) $(NAME)
	$(RM) $(UT)

re: fclean all

dbg: CFLAGS += -g
dbg: re

.PHONY: all build clean fclean