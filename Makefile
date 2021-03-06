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
	src/components/friction_component.c \
	src/components/friction_giver.c \
	src/components/clickable_component.c \
	src/components/input_component.c \
	src/components/tag_component.c \
	src/components/tooltip_component.c \
	src/components/map_linker.c \
	src/components/renderers/sprite_renderer.c \
	src/components/renderers/anim_renderer.c \
	src/components/renderers/anim_utils.c \
	src/components/renderers/text_renderer.c \
	src/components/renderers/map_renderer.c \
	src/scene/scene.c \
	src/scene/scene_constructor.c \
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
	src/systems/friction_system.c \
	src/systems/tooltip_system.c \
	src/systems/clickable_system.c \
	src/systems/fixed_to_cam_pseudosystem.c \
	src/systems/map_linker_system.c \
	src/engine/engine_system_builder.c \
	src/engine/engine_component_builder.c \
	src/engine/event_manager.c \
	src/utility/vector2.c \
	src/utility/my_realloc.c \
	src/sfml_renderer/sfml_dataloaders.c \
	src/sfml_renderer/sfml_music_player.c \
	src/sfml_renderer/texture_utility.c \
	src/sfml_renderer/sfml_drawer.c \
	src/sfml_renderer/sfml_functions.c \
	src/sfml_renderer/sfml_vertex.c \
	src/sfml_renderer/sfml_events.c \
	src/sfml_renderer/sfml_init.c \
	src/ui/setup_ui.c \
	src/ui/button.c \
	src/ui/tooltip.c \
	src/isometry/isometry.c \
	src/isometry/map_utils.c \
	src/isometry/tile_collisions.c \
	src/components/vertex_component.c \
	src/isometry/vertex_data_loader.c \
	src/sfml_renderer/sfml_utilities.c

OBJ = $(SRC:%.c=%.o)

INCLUDE = -I ./include

CFLAGS = $(INCLUDE) -Wall -Wshadow -Wextra -Wno-unused-parameter

NAME = libgamacon.a

CC = gcc

AR = ar rc

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

dbg: CFLAGS += -g
dbg: re

.PHONY: all build clean fclean