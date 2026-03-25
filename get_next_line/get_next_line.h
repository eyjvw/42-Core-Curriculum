/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 04:05:10 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:45:38 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 400
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	ft_strncpy(char *dst, char *src, size_t n);
void	ft_strcpy(char *dst, char *src);

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, char c);

size_t	ft_strlen(char *s);

#endif