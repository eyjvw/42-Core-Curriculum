/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:30:35 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:11:05 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "others.h"

void	ft_kill(t_game *game, uint8_t status)
{
	delete_data(&game->data);
	kill_display(&game->display);
	exit (status);
}

int	close_game(t_game *game)
{
	ft_kill((t_game *)game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
