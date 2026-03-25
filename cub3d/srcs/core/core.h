/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:36:13 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:37:05 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H
# include "structs.h"
# include "io.h"

//Arg check
void		check_path(char *path);
void		check_args(int ac, char **av);

//Init
void		game_init(char *file, t_game *game);

//Utils
int			rgb_to_hex(uint8_t *rgb);
float		angle_to_radian(int angle);
bool		is_wall(char **map, int x, int y);

#endif
