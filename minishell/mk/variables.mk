NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
SRCS = main.c \
	sources/ast/ft_ast.c \
	sources/ast/ft_parse_and_or.c \
	sources/ast/ft_parse_command.c \
	sources/ast/ft_parse_group.c \
	sources/ast/ft_parse_pipe.c \
	sources/ast/ft_parse_redir.c \
	sources/built-in/ft_env.c \
	sources/built-in/ft_pwd.c \
	sources/built-in/ft_cd.c \
	sources/built-in/ft_exit.c \
	sources/built-in/ft_echo.c \
	sources/built-in/ft_unset.c \
	sources/built-in/ft_export.c \
	sources/exec/ft_exec_and.c \
	sources/exec/ft_exec_ast.c \
	sources/exec/ft_exec_builtin.c \
	sources/exec/ft_exec_cmd.c \
	sources/exec/ft_exec_heredoc.c \
	sources/exec/ft_exec_node.c \
	sources/exec/ft_exec_or.c \
	sources/exec/ft_exec_pipe.c \
	sources/exec/ft_exec_redir.c \
	sources/exec/ft_exec_subshell.c \
	sources/expand/ft_expand_variables.c \
	sources/expand/ft_expand_wildcard.c \
	sources/expand/ft_expand.c \
	sources/tokenizer/ft_check_args.c \
	sources/tokenizer/ft_tokenizer_meta.c \
	sources/tokenizer/ft_tokenizer_word.c \
	sources/tokenizer/ft_tokenizer.c \
	sources/utils/ft_bzero.c \
	sources/utils/ft_count_args.c \
	sources/utils/ft_create_ast.c \
	sources/utils/ft_create_env.c \
	sources/utils/ft_create_token.c \
	sources/utils/ft_env_to_arr.c \
	sources/utils/ft_final_clean.c \
	sources/utils/ft_get_env.c \
	sources/utils/ft_get_path.c \
	sources/utils/ft_init_env.c \
	sources/utils/ft_is_builtin.c \
	sources/utils/ft_is_op.c \
	sources/utils/ft_is_red.c \
	sources/utils/ft_isalnum.c \
	sources/utils/ft_ismeta.c \
	sources/utils/ft_isspace.c \
	sources/utils/ft_itoa.c \
	sources/utils/ft_lst_addback.c \
	sources/utils/ft_mini_clean.c \
	sources/utils/ft_putstr_fd.c \
	sources/utils/ft_remove_quotes.c \
	sources/utils/ft_split.c \
	sources/utils/ft_strchr.c \
	sources/utils/ft_strcmp.c \
	sources/utils/ft_strdup.c \
	sources/utils/ft_strjoin.c \
	sources/utils/ft_strlen.c \
	sources/utils/ft_substr.c \
	sources/signals/ft_sigquit.c \
	sources/signals/ft_sigint.c \
	sources/signals/ft_reset.c \
	sources/utils/ft_add_env.c \
	sources/utils/ft_strncmp.c

OBJS = $(SRCS:.c=.o)
