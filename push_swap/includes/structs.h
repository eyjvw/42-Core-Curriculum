/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:43:15 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/11 05:51:30 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef struct t_stack
{
	int				content;
	int				index;
	struct t_stack	*next;
}	t_stack;

typedef struct t_all
{
	t_stack	*a;
	t_stack	*b;
}	t_all;
