/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student,42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:25 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/13 08:05:08 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact():firstName("None"), lastName("None"), nickName("None"), phoneNumber("None"), secret("None") {}
Contact::Contact(std::string firstName, std::string lastName, std::string nickName, std::string phoneNumber, std::string secret): firstName(firstName), lastName(lastName), nickName(nickName), phoneNumber(phoneNumber), secret(secret) {}

std::string truncate(std::string data)
{
	if (data.length() > 10)
		return (data.substr(0, 9) + ".");
	return (data);
}

void	Contact::showAll(void)
{
	std::cout << "[PhoneBook] First Name : " << this->firstName << std::endl;
	std::cout << "[PhoneBook] Last Name : " << this->lastName << std::endl;
	std::cout << "[PhoneBook] Nick Name : " << this->nickName << std::endl;
	std::cout << "[PhoneBook] Phone Number : " << this->phoneNumber << std::endl;
	std::cout << "[PhoneBook] Secret : " << this->secret << std::endl;
}

void	Contact::showInfo(int id)
{
	std::cout << "│" << std::setw(10) << id + 1;
	std::cout << "│" << std::setw(10) << truncate(this->firstName);
	std::cout << "│" << std::setw(10) << truncate(this->lastName);
	std::cout << "│" << std::setw(10) << truncate(this->nickName);
	std::cout << "│" << std::endl;
}

std::string	Contact::getFirstName(void)
{
	return (this->firstName);
}

std::string	Contact::getLastName(void)
{
	return (this->lastName);
}

std::string	Contact::getNickName(void)
{
	return (this->nickName);
}

Contact::~Contact(void) {}