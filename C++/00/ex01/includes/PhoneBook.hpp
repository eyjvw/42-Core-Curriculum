/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:38 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 02:51:18 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Contact.hpp"
#include <cstdlib>
#include <cctype>

class PhoneBook
{
	private:
		int contacts_number;
		int next_index;
		Contact contacts[8];

		void add(std::string firstName, std::string lastName, std::string nickName, std::string phoneNumber, std::string secret);
		void search(void);

	public:
		PhoneBook(void);
		~PhoneBook(void);
		
		void addCommand(void);
		void searchCommand(void);
};