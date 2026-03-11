/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 03:05:42 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:36:13 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"
# include <stddef.h>

void	ft_putstr_fd(int fd, char *str);
void	ft_init(t_pipex *px, int ac, char **av, char **env);
void	ft_here_doc(t_pipex *px);
void	ft_open(t_pipex *px);
void	ft_close(t_pipex *px);
void	ft_exec(t_pipex *px, char *cmd);
void	ft_free_split(char **split, int index);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split(char *s, char c);

// get_next_line

void	ft_strncpy(char *dst, char *src, size_t n);
void	ft_strcpy(char *dst, char *src);

char	*get_next_line(int fd);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);

size_t	ft_strlen(char *s);

#endif
