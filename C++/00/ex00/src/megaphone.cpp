/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student,42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:39:00 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/13 07:20:35 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int    main(int ac, char **av)
{
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		for (int i = 1;i < ac;i++)
		{
			std::string    str(av[i]);
			std::size_t    length = str.length();

			for (std::size_t j = 0;j < length;j++)
				std::cout << (char)std::toupper(str[j]);
			if (i + 1 != ac)
				std::cout << " ";
		}
	}
}