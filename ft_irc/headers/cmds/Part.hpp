/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:00:00 by sbonneau          #+#    #+#             */
/*   Updated: 2026/10/19 15:00:00 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "Server.hpp"

class Part
{
	public:
		static bool Check(Server &server);
		static void Leave(void);
};
