/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:48:41 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 20:52:26 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include "ui.h"
# include "io.h"
# include "libft.h"
# include "graphics.h"
# include "others.h"

# define RES_X			1920
# define RES_Y			1080
# define FOV			90

//Points
t_point		get_point(float x, float y);
void		print_point(t_point vec, const char *name);
t_point		rotate_point_around(t_point center, t_point point, double angle);

//Draw
void		my_mlx_pixel_put(t_img *data, t_point px, int color);
void		draw_line(t_img *img, t_point start, t_point end, int color);
void		draw_square(t_img *img, t_point start, int size, int color);
void		draw_rectangle(t_img *img, t_point pos, int len, int hei);

//DDA
t_point		get_delta(t_point dir);
t_ddata		dda(t_point player, char **map, t_ray *ray);
float		get_wallx(t_ddata *dda, t_point dir, t_point player);
float		get_walldist(t_ddata *dda, t_point player, t_point dir);

//Raycast
void		raycast(t_game *game);
void		init_ray(t_ray *ray, t_ddata *dda);
void		vertical_draw(t_game *game, t_ray ray);;
void		draw_ceil(t_img *frame, int color);
void		draw_floor(t_img *frame, int color);

//Renderer
int			render(t_game *game);
uint32_t	get_time(void);

//Display management
bool		init_display(t_display *display, t_data *data);
void		kill_display(t_display *display);
void		ft_kill(t_game *game, uint8_t status);
int			close_game(t_game *game);

#endif
