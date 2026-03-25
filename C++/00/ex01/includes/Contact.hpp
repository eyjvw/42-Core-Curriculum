/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:44:21 by sbonneau          #+#    #+#             */
/*   Updated: 2026/03/25 02:51:12 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>

class Contact
{
	private:
		std::string firstName;
		std::string lastName;
		std::string nickName;
		std::string phoneNumber;
		std::string secret;

	public:
		Contact(void);
		Contact(std::string firstName, std::string lastName, std::string nickName, std::string phoneNumber, std::string secret);
		~Contact(void);
		
		void showAll(void);
		void showInfo(int id);

		std::string getFirstName(void);
		std::string getLastName(void);
		std::string getNickName(void);

		
};