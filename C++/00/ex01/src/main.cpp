/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:21 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 02:47:14 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static void	display_usage(void)
{
	std::cout << std::endl;
	std::cout << "[PhoneBook] Usage of the phone book :" << std::endl;
	std::cout << "[PhoneBook] ADD    => Allow you to add a new contact" << std::endl;
	std::cout << "[PhoneBook] SEARCH => Allow you to find a contact" << std::endl;
	std::cout << "[PhoneBook] EXIT   => Exit the phonebook" << std::endl;
	std::cout << "[PhoneBook] This phonebook has a limit of 8 contacts" << std::endl;
	std::cout << std::endl;
}

int	main(void)
{
	PhoneBook	phonebook;
	std::string	input;
	
	display_usage();
	
	while (1)
	{
		std::cout << "[PhoneBook] Command : ";
		if (!std::getline(std::cin, input))
			break ;
		else if (input == "ADD")
			phonebook.addCommand();
		else if (input == "SEARCH")
			phonebook.searchCommand();
		else if (input == "EXIT")
			break ;
		else
			display_usage();
	}
	return (0);
}
