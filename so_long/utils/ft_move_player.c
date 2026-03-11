/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:42:57 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/08 05:44:54 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_find_player(t_game *game, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	ft_print_infos(t_game *game)
{
	ft_pinfo(INFO_MOVES_COUNT);
	ft_putnbr_fd(1, game->moves);
	ft_putstr_fd(1, INFO_COLLECTIBLES);
	ft_putnbr_fd(1, game->collectibles_collected);
	ft_putstr_fd(1, "\n");
}

static void	ft_check(t_game *game, int *tab)
{
	if (tab[2] < 0 || tab[2] >= game->map->width
		|| tab[3] < 0 || tab[3] >= game->map->height)
		return ;
	if (game->map->map[tab[3]][tab[2]] == '1')
		return ;
	if (game->map->map[tab[3]][tab[2]] == 'C')
	{
		game->collectibles_collected++;
		game->map->map[tab[3]][tab[2]] = '0';
	}
	if (game->map->map[tab[3]][tab[2]] == 'M')
		(ft_perror("Le joueur est mort"), ft_clean_exit(game, 0));
	game->player_on_exit = (game->map->map[tab[3]][tab[2]] == 'E');
	if (game->collectibles_collected == game->map->collectibles
		&& game->map->map[tab[3]][tab[2]] == 'E')
		(ft_psuccess(SUCCESS_GAME), ft_clean_exit(game, 0));
	if (tab[0] == game->map->exit_x && tab[1] == game->map->exit_y)
		game->map->map[tab[1]][tab[0]] = 'E';
	else
		game->map->map[tab[1]][tab[0]] = '0';
	game->map->map[tab[3]][tab[2]] = 'P';
	game->moves++;
	ft_print_infos(game);
}

void	ft_move_player(t_game *game, int dx, int dy)
{
	int	tab[4];
	int	px;
	int	py;

	ft_find_player(game, &px, &py);
	tab[0] = px;
	tab[1] = py;
	tab[2] = px + dx;
	tab[3] = py + dy;
	ft_check(game, tab);
	ft_render(game);
}
