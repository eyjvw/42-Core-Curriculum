NAME = libft.a

SOURCES = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		  ft_tolower.c ft_toupper.c ft_strlen.c ft_strchr.c ft_atoi.c ft_memset.c \
		  ft_bzero.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_strlcpy.c \
		  ft_strlcat.c ft_strdup.c ft_putendl_fd.c ft_calloc.c ft_memchr.c ft_strjoin.c \
		  ft_substr.c ft_strncmp.c ft_strnstr.c ft_split.c ft_strtrim.c ft_itoa.c ft_striteri.c \
		  ft_memcpy.c ft_memcmp.c ft_strmapi.c ft_memmove.c ft_strrchr.c

BONUS_SOURCES = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
				ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c \
				ft_lstsize_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(OBJ_DIR)/,$(BONUS_SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -f
CC = cc
