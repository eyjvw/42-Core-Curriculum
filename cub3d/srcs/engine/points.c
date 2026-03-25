/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 21:55:18 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 19:28:17 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	print_point(t_point vec, const char *name)
{
	printf("%s : [x : %f][y : %f]\n", name, vec.x, vec.y);
}

t_point	get_point(float x, float y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point	rotate_point_around(t_point center, t_point point, double angle)
{
	t_point	rel;
	t_point	result;
	t_point	rotated;

	rel.x = point.x - center.x;
	rel.y = point.y - center.y;
	rotated.x = rel.x * cos(angle) - rel.y * sin(angle);
	rotated.y = rel.x * sin(angle) + rel.y * cos(angle);
	result.x = rotated.x + center.x;
	result.y = rotated.y + center.y;
	result.x = rotated.x + center.x;
	result.y = rotated.y + center.y;
	return (result);
}
