/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 06:39:32 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/08 05:25:36 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_check_rectangular(char **map)
{
	unsigned long	len;
	int				i;

	if (!map || !map[0] || map[0][0] == '\0')
		return (0);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_walls(char **map)
{
	int	rows;
	int	cols;
	int	i;

	rows = 0;
	while (map[rows])
		rows++;
	if (rows == 0)
		return (0);
	cols = ft_strlen(map[0]);
	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_increments(char **m, int *p, int *ee, int *c)
{
	int	i;
	int	j;

	i = 0;
	while (m[i])
	{
		j = 0;
		while (m[i][j])
		{
			if (m[i][j] == 'P')
				(*p)++;
			else if (m[i][j] == 'E')
				(*ee)++;
			else if (m[i][j] == 'C')
				(*c)++;
			else if (m[i][j] != '0' && m[i][j] != '1' && m[i][j] != 'M')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_check_elems(t_game *game)
{
	int		player;
	int		exit_e;
	int		collectibles;
	char	**map;

	player = 0;
	exit_e = 0;
	collectibles = 0;
	map = game->map->map;
	if (!ft_increments(map, &player, &exit_e, &collectibles))
		return (0);
	if ((player == 1 && exit_e == 1 && collectibles >= 1))
	{
		game->map->collectibles = collectibles;
		return (1);
	}
	return (0);
}

void	ft_check_map(t_game *game)
{
	ft_save_pos(game);
	if (!ft_check_rectangular(game->map->map))
		return (ft_perror(ERR_NOT_RECTANGULAR), ft_clean_exit(game, 2));
	ft_pinfo(INFO_RECTANGULAR);
	if (!ft_check_walls(game->map->map))
		return (ft_perror(ERR_NOT_CLOSE), ft_clean_exit(game, 2));
	ft_pinfo(INFO_CLOSE);
	if (!ft_check_elems(game))
		return (ft_perror(ERR_ELEMS),
			ft_clean_exit(game, 2));
	ft_pinfo(INFO_ELEMS);
	if (!ft_is_possible(game))
		return (ft_perror(ERR_NOT_POSSIBLE),
			ft_clean_exit(game, 2));
	ft_pinfo(INFO_POSSIBLE);
	ft_psuccess(INFO_MAP_VALID);
}
