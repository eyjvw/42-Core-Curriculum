/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:01:22 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 18:07:13 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include "errors.h"
# include "libft.h"
# include "cub_interpreter.h"
# define MAP_BUFFER			10
# define MAP_SET			" 01NSEWD"
# define PLAYER_SET			"NEWS"
# define SPACE_CHARS		" \t\n\v\f\r"
# define CHECK_MISSING		true
# define INVALID_FD			-1
# define RGB_LEN_MAX		11
# define EIGHT_BITS_MAX		255
# define RGB_FIELD_LEN_MAX	3
# define RGB_MAX_FIELD		3
# define DOOR_BASE_AMOUNT	5

enum e_rgb_data
{
	LEN,
	FIELD_LEN,
	FIELD_VALUE,
	FIELD_COUNT
};

//Main handling
int8_t	check_id(const char *id, size_t line, bool check_mod);
bool	check_link(const char *link, size_t line, t_data *data, int8_t id);
bool	check_color(const char *color, size_t line, t_data *data, int8_t id);
bool	check_map(int fd, char *line, size_t line_n, t_data *data);

//Map handling
bool	check_player(char c, size_t line_n);
bool	check_map_line(char *line, size_t line_n);
bool	flood_fill(t_data *data, int x, int y, bool *closed);
bool	find_player(t_data *data);

//Doors
void	add_door(t_data *data, int x, int y);
void	replace_doors(t_data *data);

#endif
