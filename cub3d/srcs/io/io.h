/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:36:52 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:57:27 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H
# include <math.h>
# include "mlx.h"
# include "others.h"
# include "graphics.h"

# define MOVE_SPEED		0.1
# define ROTATE_SPEED	0.0872

# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_F			102
# define MCLICK_L		1

# define KPRESS			2
# define KREL			3
# define BPRESS			4
# define MOTION			6
# define DESTROY		17

# define KPRESSMASK		1
# define KRELMASK		2
# define BPRESSMASK		4
# define PMOTIONMASK	64

enum e_key_ids
{
	KW_ID,
	KA_ID,
	KS_ID,
	KD_ID,
	KF_ID,
	KLEFT_ID,
	KRIGHT_ID,
	MCLICKL_ID
};

//Key events
void		hooks(t_game *game);
int			handle_input(t_game *game);

//Movements
void		move_left(t_game *game);
void		move_right(t_game *game);
void		move_forward(t_game *game);
void		move_backward(t_game *game);

//Mouse
int			mouse_move(int x, int y, t_game *game);
void		turn_right(t_game *game, int diff, bool mouse);
void		turn_left(t_game *game, int diff, bool mouse);

#endif
