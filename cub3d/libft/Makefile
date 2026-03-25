CC=cc
FLAGS=-Werror -Wall -Wextra -g3
SRCS=ft_isset.c \
	 ft_isalpha.c \
	 ft_isdigit.c \
	 ft_isalnum.c \
	 ft_isascii.c \
	 ft_isprint.c \
	 ft_isspace.c \
	 ft_toupper.c \
	 ft_tolower.c \
	 ft_strlen.c \
	 ft_memset.c \
	 ft_bzero.c \
	 ft_memcpy.c \
	 ft_memmove.c \
	 ft_memchr.c \
	 ft_memcmp.c \
	 ft_strchr.c \
	 ft_strrchr.c \
	 ft_strncmp.c \
	 ft_strcmp.c \
	 ft_strtok.c \
	 ft_strnstr.c \
	 ft_atoi.c \
	 ft_calloc.c \
	 ft_realloc.c \
	 ft_strdup.c \
	 ft_substr.c \
	 ft_strjoin.c \
	 ft_strtrim.c \
	 ft_split.c \
	 ft_itoa.c \
	 ft_write.c \
	 ft_write_error.c \
	 ft_write_errorn.c \
	 ft_doubledup.c \
	 ft_strmaxlen.c \
	 ft_doublelen.c \
	 ft_double_free.c \
	 ft_double_realloc.c \
	 ft_double_write.c \
	 ft_get_row_id.c \
	 ft_add_row.c \
	 ft_delete_row.c \
	 ft_replace_row.c \
	 ft_putchar_fd.c \
	 ft_putstr_fd.c \
	 ft_putendl_fd.c \
	 ft_putnbr_fd.c \
	 ft_lstnew_bonus.c \
	 ft_lstadd_front_bonus.c \
	 ft_lstsize_bonus.c \
	 ft_lstlast_bonus.c \
	 ft_lstadd_back_bonus.c \
	 ft_lstdelone_bonus.c \
	 ft_lstclear_bonus.c \
	 ft_lstiter_bonus.c \
	 ft_lstmap_bonus.c \
	 get_next_line.c \
	 get_next_line_utils.c \
	 ft_dump_file.c
OBJS=$(SRCS:.c=.o)
NAME=libft.a
HEADER=libft.h

.PHONY: all start $(NAME)

all: start $(NAME)

start:
	@echo "\e[1;33m===============LIBFT==============="

$(NAME): $(OBJS) $(HEADER)
	@echo "\e[1;32m [LIBFT] Building library..."
	@ar rcs $(NAME) $(OBJS)
	@echo "\e[1;32m [LIBFT] Build Complete !"

%.o: %.c
	@echo "\e[1;32m [LIBFT] Compiling $^"
	@$(CC) $(FLAGS) $^ -c -o $@

fclean: clean
	@echo "\e[1;31m [DELETING LIBRARY]"
	@rm -f $(NAME)

clean:
	@echo "\e[1;31m [DELETING RESIDUAL FILES]"
	@rm -f $(OBJS)

re: clean all
