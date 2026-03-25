/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:44:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:41:08 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

t_stack	*ft_create_stack(int content);
int		ft_atoi(char *str, int *numbers);
int		ft_has_dup(int *arr, int len);
int		ft_size_stack(t_stack *stack);
int		ft_is_num(char *str);
int		ft_min_index(t_stack *stack);
int		ft_max_index(t_stack *stack);
int		ft_index_pos(t_stack *stack, int index);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_clean_exit(t_all *all, int code);
void	*ft_memset(void *s, int c, size_t x);
void	ft_putstr_fd(int fd, char *str);
void	ft_check_and_init(t_all *all, int ac, char **av);
void	ft_free_split(char **split, int index);
void	ft_pa(t_all *all);
void	ft_pb(t_all *all);
void	ft_sa(t_all *all, int print);
void	ft_sb(t_all *all, int print);
void	ft_ss(t_all *all);
void	ft_ra(t_all *all, int print);
void	ft_rb(t_all *all, int print);
void	ft_rr(t_all *all);
void	ft_rra(t_all *all, int print);
void	ft_rrb(t_all *all, int print);
void	ft_rrr(t_all *all);
void	ft_sort(t_all *all);
void	ft_three_sort(t_all *all);
void	ft_medium_sort(t_all *all);
void	ft_chunk(t_all *all);
void	ft_sort_to_a(t_all *all);
void	ft_init_index(t_all *all, int size, int *numbers);
void	ft_init_stacks(t_all *all, int size, int *numbers);
char	**ft_split(char *s, char c);