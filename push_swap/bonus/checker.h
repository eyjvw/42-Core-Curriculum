/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 05:09:03 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:41:18 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define BUFFER_SIZE 100

#include "../includes/push_swap.h"

void	pa(t_all *all);
void	pb(t_all *all);
void	sa(t_all *all);
void	sb(t_all *all);
void	ss(t_all *all);
void	ra(t_all *all);
void	rb(t_all *all);
void	rr(t_all *all);
void	rra(t_all *all);
void	rrb(t_all *all);
void	rrr(t_all *all);

// get_next_line
char	*get_next_line(int fd);
void	ft_strncpy(char *dst, char *src, size_t n);
void	ft_strcpy(char *dst, char *src);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);