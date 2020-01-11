##
## EPITECH PROJECT, 2019
## Gamacon
## File description:
## Makefile
##

SRC = src/engine/engine.c \
	src/engine/engine_internal.c \
	src/engine/discard_player.c \
	src/engine/engine_dataloader.c \
	src/entity/entity.c \
	src/entity/entity_factory.c \
	src/component.c \
	src/components/movable_component.c \
	src/components/collision_component.c \
	src/components/transform_component.c \
	src/components/renderer.c \
	src/components/camera_follow.c \
	src/components/fixed_to_cam.c \
	src/components/parallax_component.c \
	src/components/controllable_component.c \
	src/components/friction_component.c \
	src/components/friction_giver.c \
	src/components/controllers/keyboard_controller.c \
	src/components/renderers/sprite_renderer.c \
	src/components/renderers/anim_renderer.c \
	src/components/renderers/text_renderer.c \
	src/scene/scene.c \
	src/scene/scene_loader.c \
	src/scene/scene_destroy.c \
	src/utility/arraylen.c \
	src/utility/list.c \
	src/utility/tupple.c \
	src/deserializer/deserialize_entity.c \
	src/deserializer/prefab.c \
	src/system.c \
	src/systems/sfml_renderer_system.c \
	src/systems/movable_system.c \
	src/systems/camera_follow_system.c \
	src/systems/collision_system.c \
	src/systems/parallax_system.c \
	src/systems/controllers/keyboard_controller_system.c \
	src/systems/friction_system.c \
	src/systems/fixed_to_cam_pseudosystem.c \
	src/engine/engine_system_builder.c \
	src/engine/engine_component_builder.c \
	src/utility/vector2.c \
	src/utility/my_realloc.c \
	src/sfml_renderer/sfml_dataloaders.c \
	src/sfml_renderer/sfml_music_player.c \
	src/sfml_renderer/texture_utility.c \
	src/sfml_renderer/sfml_drawer.c \
	src/sfml_renderer/sfml_functions.c

OBJ = $(SRC:%.c=%.o)

GCDA = *.gcda

GCNO = *.gcno

TESTS = tests/deserializations.c \
	tests/game_loop.c

INCLUDE = -I ./include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra

LDFLAGS = -L ../my -L ../xmlparser -L ../quadtree\
-lxmlparser -lquadtree -lmy -lcsfml-system -lcsfml-graphics -lcsfml-window -lm

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
	$(RM) $(GCDA)
	$(RM) $(GCNO)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(UT)

re: fclean all

dbg: CFLAGS += -g
dbg: re

.PHONY: all build clean fclean