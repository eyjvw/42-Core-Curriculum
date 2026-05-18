/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:28:33 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 02:14:40 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	OR_IF,
	AND_IF,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	LPAREN,
	RPAREN
}	t_token_type;

typedef enum e_state_type
{
	PROMPT,
	EXEC,
	STATE_HERE_DOC,
}	t_state_type;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_REDIR,
	AST_SUBSHELL
}	t_ast_type;

typedef struct s_tokens
{
	struct s_tokens	*next;
	char			*value;
	t_token_type	type;
}	t_tokens;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

typedef struct s_ast
{
	t_ast_type		type;
	char			**argv;
	char			*file;
	t_token_type	redir_type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_shell
{
	t_env			*env;
	t_tokens		*tokens;
	t_ast			*ast;
	char			*input;
	int				exit_code;
}	t_shell;

typedef struct s_node
{
	struct s_node	*next;
}	t_node;

#endif
