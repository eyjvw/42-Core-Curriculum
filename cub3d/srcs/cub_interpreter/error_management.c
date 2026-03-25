/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 01:42:16 by hkeromne          #+#    #+#             */
/*   Updated: 2026/01/12 16:09:35 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"

void	system_error(uint8_t error)
{
	ft_write_error("System errror : ");
	if (error == MALLOC)
		ft_write_errorn("Malloc failed");
	ft_write_errorn("Exit program...");
	exit (EXIT_FAILURE);
}

void	invalid_error(size_t line, uint8_t error)
{
	ft_write_error(" Format: line ");
	ft_putnbr_fd(line, 2);
	ft_write_error(": Invalid ");
	if (error == SYNTAX)
		ft_write_errorn("Syntax");
	else if (error == LINK)
		ft_write_errorn("Link");
	else if (error == COLOR)
		ft_write_errorn("Color");
	else if (error == ID)
		ft_write_errorn("Identifier");
	else if (error == MAP)
		ft_write_errorn("Map");
}

void	duplicate_error(size_t line, uint8_t duplicate)
{
	ft_write_error(" Format: line ");
	ft_putnbr_fd(line, 2);
	ft_write_error(": Duplicate ");
	if (duplicate == NO)
		ft_write_errorn("Texture : NORTH");
	else if (duplicate == SO)
		ft_write_errorn("Texture : SOUTH");
	else if (duplicate == WE)
		ft_write_errorn("Texture : WEST");
	else if (duplicate == EA)
		ft_write_errorn("Texture : EAST");
	else if (duplicate == F)
		ft_write_errorn("Color : floor");
	else if (duplicate == C)
		ft_write_errorn("Color : ceiling");
	else if (duplicate == D)
		ft_write_errorn("Texture : Door");
	else if (duplicate == PLAYER)
		ft_write_errorn("Player");
}

void	missing_error(uint8_t missing)
{
	ft_write_error(": Missing ");
	if (missing == NO)
		ft_write_errorn("Texture : NORTH");
	else if (missing == SO)
		ft_write_errorn("Texture : SOUTH");
	else if (missing == WE)
		ft_write_errorn("Texture : WEST");
	else if (missing == EA)
		ft_write_errorn("Texture : EAST");
	else if (missing == F)
		ft_write_errorn("Color : floor");
	else if (missing == C)
		ft_write_errorn("Color : ceiling");
	else if (missing == D)
		ft_write_errorn("Texture : Door");
	else if (missing == MAP)
		ft_write_errorn("Element : Map");
	else if (missing == PLAYER)
		ft_write_errorn("Element : Player");
}

void	parse_error(uint8_t mode, uint8_t error, size_t line)
{
	ft_write_error("ERROR: File");
	if (mode == INVALID)
		invalid_error(line, error);
	else if (mode == DUPLICATE)
		duplicate_error(line, error);
	else
		missing_error(error);
}
