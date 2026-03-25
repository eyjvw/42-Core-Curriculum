/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 04:06:24 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 03:48:35 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs.h"

void			ft_clear_fd(const int fd);
void			ft_putstr_fd(const int fd, const char *str);
void			ft_perror(const char *str);
void			ft_pinfo(const char *str);
char			*ft_read(const int fd);
char			*ft_strjoin(char *s1, const char *s2);
char			**ft_split(const char *s, char c);
char			**ft_get_map(const char *filename);
unsigned long	ft_strlen(const char *str);
void			ft_strncpy(char *dest, const char *src, unsigned long n);
void			ft_clean_exit(t_game *game, int code);
void			ft_bzero(void *s, unsigned long n);
void			ft_init_cli(void);
void			ft_check_map(t_game *game);
void			ft_psuccess(const char *str);
void			ft_init_window(t_game *game);
unsigned int	ft_arrlen(const char **str);
void			ft_load_textures(t_game *game);
void			ft_render(t_game *game);
int				ft_handle_close(t_game *game);
int				ft_handle_key(int keycode, t_game *game);
void			ft_move_player(t_game *game, int dx, int dy);
void			ft_save_pos(t_game *game);
void			ft_putnbr_fd(int fd, int nb);
void			ft_putnbr_fd(int fd, int nb);
int				ft_is_possible(t_game *game);
char			*ft_fusion(const char *str, int n);
