/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <student@42lehavre.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:01:07 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 16:10:35 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum e_err_sys
{
	MALLOC
};

enum e_err_mode
{
	MISSING,
	DUPLICATE,
	INVALID
};

enum e_err_obj
{
	NO,
	SO,
	WE,
	EA,
	D,
	F,
	C,
	MAP,
	PLAYER,
	TEXTURE,
	SYNTAX,
	COLOR,
	LINK,
	ID
};

void	system_error(uint8_t error);
void	parse_error(uint8_t mode, uint8_t error, size_t line);

#endif
