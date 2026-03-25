/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:36:09 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:57:41 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHERS_H
# define OTHERS_H
# include "engine.h"
# include <stdlib.h>
# include <unistd.h>

# define PI				3.141592

enum e_arg_errors
{
	TOO_MANY_ARGS,
	TOO_LITT_ARGS,
	INVALID_PATH,
	INVALID_FORMAT,
	INVALID_RES
};

void		write_error(uint8_t error);
void		ft_exit(ssize_t	error);
void		ft_kill(t_game *game, uint8_t status);
int			close_game(t_game *game);
bool		is_wall(char **map, int x, int y);
int			rgb_to_hex(uint8_t *rgb);
float		angle_to_radian(int angle);

#endif
