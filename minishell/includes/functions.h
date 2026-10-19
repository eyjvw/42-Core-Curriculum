/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:28:58 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/10 03:54:59 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

bool		ft_check_args(t_tokens *tokens);
bool		ft_tokenizer(t_shell *shell);
bool		ft_tokenizer_meta(t_tokens **tokens, char *s, int *i);
bool		ft_has_glob(char *s);
bool		ft_valid_id(char *s, int len);
bool		ft_isspace(char c);
bool		ft_ismeta(char c);
bool		ft_is_op(t_token_type type);
bool		ft_is_red(t_token_type type);
bool		ft_isalnum(char c);
bool		ft_tokenizer_word(t_tokens **tokens, char *s, int *start);
bool		ft_is_builtin(char *cmd);

size_t		ft_strlen(char *s);

char		*ft_strdup(char *str);
char		*ft_substr(char *s, int start, int len);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_and_free(char *s1, char *s2);
char		*ft_expand_variables(t_shell *shell, char *value, bool quotes);
char		*ft_expand_file(t_shell *shell, char *raw);
char		*ft_unmark(char *s, bool glob);
char		*ft_read_line(int fd);
char		*ft_read_all(int fd);
char		*ft_get_line(t_shell *shell, char *prompt);
char		*ft_strchr(char *s, char c);
char		*ft_get_env(t_env *env, char *key);
char		*ft_get_path(t_shell *shell, char *cmd);
char		*ft_remove_quotes(char *s);

char		**ft_split(char *s, char c);
char		**ft_env_to_arr(t_env *env);
char		**ft_expand_argv(t_shell *shell, char **argv);

int			ft_strcmp(char *s1, char *s2);
int			ft_count_args(t_tokens *tokens);

int			ft_exec_cmd(t_shell *shell, t_ast *node);
int			ft_heredocs(t_shell *shell, t_ast *node);
int			ft_wait(t_shell *shell, pid_t pid);
int			ft_exec_pipe(t_shell *shell, t_ast *node);
int			ft_exec_redir(t_shell *shell, t_ast *node);
int			ft_exec_node(t_shell *shell, t_ast *node);
int			ft_exec_builtin(t_shell *shell, char **argv);
int			ft_exec_and(t_shell *shell, t_ast *node);
int			ft_exec_or(t_shell *shell, t_ast *node);
int			ft_exec_subshell(t_shell *shell, t_ast *node);
int			ft_pwd(t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_cd(t_shell *shell, char **argv);
int			ft_exit(t_shell *shell, char **argv);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_echo(char **argv);
int			ft_unset(t_shell *shell, char **argv);
int			ft_export(t_shell *shell, char **argv);

t_ast		*ft_create_ast(t_ast_type type);
t_ast		*ft_parse_and_or(t_tokens **tokens);
t_ast		*ft_parse_command(t_tokens **tokens);
t_ast		*ft_parse_group(t_tokens **tokens);
t_ast		*ft_parse_pipe(t_tokens **tokens);
t_ast		*ft_parse_redir(t_tokens **tokens, t_ast *cmd);

t_env		*ft_create_env(char *key, char *value);

t_tokens	*ft_create_token(char *value, t_token_type type);
t_tokens	*ft_expand_wildcards(char *pattern);
t_tokens	*ft_split_words(char *s);

void		ft_init_env(t_shell *shell, char **env);
void		ft_mini_clean(t_shell *shell);
void		ft_final_clean(t_shell *shell);
void		ft_lst_addback(void **lst, void *new);
void		ft_bzero(void *s, size_t n);
void		ft_putstr_fd(int fd, char *s);
void		ft_ast(t_shell *shell);
void		ft_exec_ast(t_shell *shell);
void		ft_sigquit(void);
void		ft_sigint(t_state_type type);
void		ft_reset(void);
void		ft_add_env(t_shell *shell, char *key, char *value);
void		ft_exit_child(t_shell *shell, int code);
void		ft_close_fds(t_ast *ast);
void		ft_free_arr(char **arr);
void		ft_error(char *cmd, char *arg, char *msg);
void		ft_invalid_id(char *cmd, char *arg);

#endif
