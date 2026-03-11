NAME = pipex

SOURCES = main.c \
		  src/ft_close.c \
		  src/ft_exec.c \
		  src/ft_here_doc.c \
		  src/ft_init.c \
		  src/ft_open.c \
		  src/ft_putstr_fd.c \
		  src/ft_split.c \
		  src/ft_strcmp.c \
		  src/ft_strncmp.c \
		  src/get_next_line.c \
		  src/get_next_line_utils.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I includes/
RM = rm -f
CC = cc
