/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 07:06:19 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/07 20:26:44 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_flood_fill(t_game *game, int x, int y, char **visited)
{
	if (!game->map || !visited)
		return ;
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return ;
	if (game->map->map[y][x] == '1' || visited[y][x] == '1')
		return ;
	visited[y][x] = '1';
	ft_flood_fill(game, x + 1, y, visited);
	ft_flood_fill(game, x - 1, y, visited);
	ft_flood_fill(game, x, y + 1, visited);
	ft_flood_fill(game, x, y - 1, visited);
}

static void	ft_clean(char **visited, int len)
{
	int	i;

	if (visited)
	{
		i = 0;
		while (i < len)
		{
			if (visited[i])
				free(visited[i++]);
		}
		free(visited);
	}
}

static int	ft_check(t_game *game, char **visited)
{
	int	x;
	int	y;

	if (!visited)
		return (0);
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->map[y][x] == 'C' && !visited[y][x])
			{
				ft_clean(visited, game->map->height);
				return (0);
			}
			x++;
		}
		y++;
	}
	ft_clean(visited, game->map->height);
	return (1);
}

int	ft_is_possible(t_game *game)
{
	char	**visited;
	int		y;

	visited = malloc(sizeof(char *) * game->map->height);
	if (!visited)
		return (0);
	y = 0;
	while (y < game->map->height)
	{
		visited[y] = malloc(game->map->width + 1);
		if (!visited[y])
			return (ft_clean(visited, y), 0);
		ft_bzero(visited[y], game->map->width + 1);
		y++;
	}
	ft_flood_fill(game, game->map->player_x, game->map->player_y, visited);
	if (!visited[game->map->exit_y][game->map->exit_x])
		return (ft_clean(visited, game->map->height), 0);
	return (ft_check(game, visited));
}
