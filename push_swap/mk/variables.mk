NAME = push_swap
BONUS_NAME = checker
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
OPS_DIR = $(SRC_DIR)/ops
SORT_DIR = $(SRC_DIR)/sort
BONUS_DIR = bonus

ALL_SRC = main.c \
           $(OPS_DIR)/ft_push.c \
           $(OPS_DIR)/ft_swap.c \
           $(OPS_DIR)/ft_rotate.c \
           $(OPS_DIR)/ft_rev_rotate.c \
           $(SORT_DIR)/ft_chunk_sort.c \
           $(SORT_DIR)/ft_medium_sort.c \
           $(SORT_DIR)/ft_sort.c \
           $(SORT_DIR)/ft_three_sort.c \
           $(UTILS_DIR)/ft_atoi.c \
           $(UTILS_DIR)/ft_calloc.c \
           $(UTILS_DIR)/ft_check_and_init.c \
           $(UTILS_DIR)/ft_clean_exit.c \
           $(UTILS_DIR)/ft_create_stack.c \
           $(UTILS_DIR)/ft_find.c \
           $(UTILS_DIR)/ft_has_dup.c \
           $(UTILS_DIR)/ft_init_index.c \
           $(UTILS_DIR)/ft_init_stacks.c \
           $(UTILS_DIR)/ft_is_num.c \
           $(UTILS_DIR)/ft_memset.c \
           $(UTILS_DIR)/ft_putstr_fd.c \
           $(UTILS_DIR)/ft_size_stack.c \
           $(UTILS_DIR)/ft_split.c

BONUS_SRC = $(BONUS_DIR)/main.c \
            $(UTILS_DIR)/ft_atoi.c \
            $(UTILS_DIR)/ft_calloc.c \
            $(UTILS_DIR)/ft_check_and_init.c \
            $(UTILS_DIR)/ft_clean_exit.c \
            $(UTILS_DIR)/ft_create_stack.c \
            $(UTILS_DIR)/ft_has_dup.c \
            $(UTILS_DIR)/ft_init_index.c \
            $(UTILS_DIR)/ft_init_stacks.c \
            $(UTILS_DIR)/ft_is_num.c \
            $(UTILS_DIR)/ft_memset.c \
            $(UTILS_DIR)/ft_split.c \
            $(OPS_DIR)/ft_swap.c \
            $(BONUS_DIR)/utils/ft_push.c \
            $(BONUS_DIR)/utils/ft_rotate.c \
            $(BONUS_DIR)/utils/ft_rev_rotate.c \
            $(UTILS_DIR)/ft_putstr_fd.c \
            $(BONUS_DIR)/utils/ft_strcmp.c \
            $(BONUS_DIR)/utils/get_next_line.c \
            $(BONUS_DIR)/utils/get_next_line_utils.c

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))
BONUS_OBJECTS = $(addprefix $(BONUS_OBJ_DIR)/, $(notdir $(BONUS_SRC:.c=.o)))

CFLAGS = -O2 -Wall -Wextra -Werror -Iincludes
RM = rm -f
RM_RF = rm -rf
CC = cc
MKDIR = mkdir -p
