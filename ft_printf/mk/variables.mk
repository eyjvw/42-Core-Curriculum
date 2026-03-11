NAME = libftprintf.a

SOURCES = ft_printf.c ft_utils.c ft_utils2.c ft_utils3.c ft_conversions.c ft_conversions2.c ft_conversions3.c ft_printf_utils.c ft_bonus.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I includes/
AR = ar rcs
RM = rm -f
CC = cc
