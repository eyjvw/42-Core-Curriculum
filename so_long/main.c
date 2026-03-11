/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 03:43:28 by sbonneau          #+#    #+#             */
/*   Updated: 2025/11/11 06:07:46 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	ft_init_cli();
	if (argc != 2)
		(ft_perror(ERR_USAGE_INVALIDE),
			ft_clean_exit(&game, 1));
	if (TILE_SIZE != 48)
		(ft_perror(ERR_TILE_SIZE),
			ft_clean_exit(&game, 1));
	game.map = malloc(sizeof(t_map));
	if (!game.map)
		(ft_perror(ERR_MEMORY_MAP), ft_clean_exit(&game, 1));
	game.map->map = ft_get_map(argv[1]);
	if (!game.map->map)
		(ft_perror(ERR_READ_MAP), ft_clean_exit(&game, 1));
	ft_check_map(&game);
	ft_init_window(&game);
	ft_clean_exit(&game, 0);
	return (0);
}
