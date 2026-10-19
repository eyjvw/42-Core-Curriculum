NAME = libftprintf.a

SOURCES = src/ft_printf.c \
		  src/ft_utils.c \
		  src/ft_utils2.c \
		  src/ft_utils3.c \
		  src/ft_conversions.c \
		  src/ft_conversions2.c \
		  src/ft_conversions3.c \
		  src/ft_printf_utils.c \
		  src/ft_bonus.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
DEPS = $(OBJECTS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes/
AR = ar rcs
RM = rm -f
