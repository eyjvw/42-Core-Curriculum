NAME = push_swap
BONUS_NAME = checker

SOURCES = main.c \
		  src/ops/ft_push.c \
		  src/ops/ft_swap.c \
		  src/ops/ft_rotate.c \
		  src/ops/ft_rev_rotate.c \
		  src/sort/ft_chunk_sort.c \
		  src/sort/ft_medium_sort.c \
		  src/sort/ft_sort.c \
		  src/sort/ft_three_sort.c \
		  src/utils/ft_atoi.c \
		  src/utils/ft_calloc.c \
		  src/utils/ft_check_and_init.c \
		  src/utils/ft_clean_exit.c \
		  src/utils/ft_create_stack.c \
		  src/utils/ft_find.c \
		  src/utils/ft_has_dup.c \
		  src/utils/ft_init_index.c \
		  src/utils/ft_init_stacks.c \
		  src/utils/ft_is_num.c \
		  src/utils/ft_memset.c \
		  src/utils/ft_putstr_fd.c \
		  src/utils/ft_size_stack.c \
		  src/utils/ft_split.c

BONUS_SOURCES = bonus/main.c \
				bonus/utils/ft_push.c \
				bonus/utils/ft_rotate.c \
				bonus/utils/ft_rev_rotate.c \
				bonus/utils/ft_strcmp.c \
				bonus/utils/ft_swap.c \
				bonus/utils/get_next_line.c \
				bonus/utils/get_next_line_utils.c \
				src/utils/ft_atoi.c \
				src/utils/ft_calloc.c \
				src/utils/ft_check_and_init.c \
				src/utils/ft_clean_exit.c \
				src/utils/ft_create_stack.c \
				src/utils/ft_has_dup.c \
				src/utils/ft_init_index.c \
				src/utils/ft_init_stacks.c \
				src/utils/ft_is_num.c \
				src/utils/ft_memset.c \
				src/utils/ft_putstr_fd.c \
				src/utils/ft_split.c

OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(BONUS_OBJ_DIR)/,$(BONUS_SOURCES:.c=.o))
DEPS = $(OBJECTS:.o=.d) $(BONUS_OBJECTS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O2 -I includes/
BONUS_INC = -I bonus/
RM = rm -f
