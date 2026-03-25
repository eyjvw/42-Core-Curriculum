CC=cc
FLAGS=-Wall -Wextra -Werror -O3

SRCS=srcs/core/main.c \
	 srcs/core/init.c \
	 srcs/core/arg_check.c \
	 srcs/others/kill.c \
	 srcs/others/error.c \
	 srcs/others/utils.c \
	 srcs/ui/ui.c \
	 srcs/ui/minimap.c \
	 srcs/ui/crosshair.c \
	 srcs/io/mouse.c \
	 srcs/io/movements.c \
	 srcs/io/key_events.c \
	 srcs/engine/dda.c \
	 srcs/engine/draw.c \
	 srcs/engine/points.c \
	 srcs/engine/raycast.c \
	 srcs/engine/renderer.c \
	 srcs/engine/dda_getters.c \
	 srcs/engine/display_management.c \
	 srcs/graphics/doors.c \
	 srcs/graphics/sprite.c \
	 srcs/graphics/textures.c \
	 srcs/graphics/animations.c \
	 srcs/cub_interpreter/data.c \
	 srcs/cub_interpreter/dumper.c \
	 srcs/cub_interpreter/id_handle.c \
	 srcs/cub_interpreter/map_handle.c \
	 srcs/cub_interpreter/map_checker.c \
	 srcs/cub_interpreter/doors_handle.c \
	 srcs/cub_interpreter/link_handle.c \
	 srcs/cub_interpreter/color_handle.c \
	 srcs/cub_interpreter/error_management.c

INCLUDES = -Iheaders \
		   -Isrcs \
		   -Ilibft \
		   -Isrcs/io \
		   -Isrcs/ui \
		   -Isrcs/engine \
		   -Isrcs/others \
		   -Isrcs/graphics \
		   -Iminilibx-linux \
		   -Isrcs/cub_interpreter

LIBFT=libft.a
LIBFT_DIR=libft/

MLX_DIR = minilibx-linux/
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

OBJS=$(SRCS:.c=.o)
NAME=cub3D

.PHONY: all start $(NAME) $(LIBFT)

all: start $(MLX_DIR) $(NAME)

start:
	@echo "\e[1;33m===============CUB3D===============\e[1;30"

$(NAME): $(OBJS) $(LIBFT)
	@echo "\e[1;33m===============CUB3D===============\e[1;30"
	@echo "\e[1;32m [CUB3D] Building library...\e[1;30"
	@$(CC) $(FLAGS) $(OBJS) -L./$(LIBFT_DIR) -lft -lmlx_Linux -L./minilibx-linux/ -lXext -lX11 -lm -o $(NAME)
	@echo "\e[1;32m [CUB3D] Build Complete !\e[1;30"

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "\e[1;33m [MLX] Cloning MiniLibX...\e[0m"; \
		git clone $(MLX_REPO) $(MLX_DIR) 2>/dev/null; \
	fi
	@make -C $(MLX_DIR)

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)

%.o: %.c
	@echo "\e[1;32m [CUB3D] Compiling $^\e[1;30"
	@$(CC) $(FLAGS) $(INCLUDES) -c $^ -o $@

clean:
	@echo "\e[31m [DELETING RESIDUAL FILES]\e[1;30"
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean:	clean
	@echo "\e[31m [DELETING EXECUTABLES]\e[1;30"
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(MLX_DIR)
	@rm -f $(NAME)

re: fclean all
