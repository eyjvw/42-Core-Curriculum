/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 05:43:35 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 02:48:43 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook():contacts_number(0), next_index(0) {}

static std::string trim(const std::string &s)
{
	size_t start = 0;
	size_t end = s.length();
	while (start < end && std::isspace(static_cast<unsigned char>(s[start])))
		start++;
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		end--;
	return s.substr(start, end - start);
}

void	PhoneBook::add(std::string firstName, std::string lastName, std::string nickName, std::string phoneNumber, std::string secret)
{
	Contact	newContact(firstName, lastName, nickName, phoneNumber, secret);
	
	this->contacts[this->next_index] = newContact;
	if (this->contacts_number < 8)
		this->contacts_number++;
	this->next_index = (this->next_index + 1) % 8;
	std::cout << std::endl << "[PhoneBook] Contact added !" << std::endl << std::endl;
}

void	PhoneBook::search(void)
{
	std::string	index;
	int			newIndex;

	do {
		std::cout << "[PhoneBook] Index : ";
		if (!std::getline(std::cin, index))
			return ;
	} while (index.empty());

	for (int i = 0;index[i];i++)
	{
		if (!isdigit(index[i]) || index[i] == '0')
		{
			std::cout << "[PhoneBook] Index is out of range or invalid" << std::endl;
			return ;
		}
	}

	newIndex = atoi(index.c_str());
	if (newIndex <= this->contacts_number)
	{
		this->contacts[newIndex - 1].showAll();
		std::cout << std::endl;
		return ;
	} else {
		std::cout << "[PhoneBook] Index is out of range or invalid" << std::endl;
	}
}

void	PhoneBook::addCommand()
{
	std::string	firstName;
	std::string	lastName;
	std::string	nickName;
	std::string	phoneNumber;
	std::string	secret;

	std::cout << std::endl;
	
	do {
		std::cout << "[PhoneBook] First Name : ";
		if (!std::getline(std::cin, firstName))
			return ;
		firstName = trim(firstName);
	} while (firstName.empty());

	do {
		std::cout << "[PhoneBook] Last Name : ";
		if (!std::getline(std::cin, lastName))
			return ;
		lastName = trim(lastName);
	} while (lastName.empty());

	do {
		std::cout << "[PhoneBook] Nick Name : ";
		if (!std::getline(std::cin, nickName))
			return ;
		nickName = trim(nickName);
	} while (nickName.empty());

	do {
		std::cout << "[PhoneBook] Phone Number : ";
		if (!std::getline(std::cin, phoneNumber))
			return ;
		phoneNumber = trim(phoneNumber);
	} while (phoneNumber.empty());

	do {
		std::cout << "[PhoneBook] Secret : ";
		if (!std::getline(std::cin, secret))
			return ;
		secret = trim(secret);
	} while (secret.empty());

	add(firstName, lastName, nickName, phoneNumber, secret);
}

void	PhoneBook::searchCommand()
{
	if (this->contacts_number == 0)
	{
		std::cout << std::endl << "[PhoneBook] No contact have been added" << std::endl << std::endl;
		return ;
	}

	std::cout << "┌──────────┬──────────┬──────────┬──────────┐" << std::endl;
	std::cout << "│   index  │first name│ last name│ nickname │" << std::endl;
	std::cout << "├──────────┼──────────┼──────────┼──────────┤" << std::endl;
	for (int i = 0;i < this->contacts_number;i++)
		this->contacts[i].showInfo(i);
	std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
	search();
}

PhoneBook::~PhoneBook(void) {}