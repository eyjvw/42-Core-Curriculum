/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:59:22 by sbonneau          #+#    #+#             */
/*   Updated: 2025/12/15 06:43:48 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void)
{
	std::string	string = "HI THIS IS BRAIN";
	std::string	*stringPTR = &string;
	std::string &stringREF = string;

	std::cout << "Memory address of string : " << &string << std::endl;
	std::cout << "Memory address of stringPTR : " << stringPTR << std::endl;
	std::cout << "Memory address of stringREF : " << &stringREF << std::endl;

	std::cout << "Value of string : " << string << std::endl;
	std::cout << "Value of stringPTR : " << *stringPTR << std::endl;
	std::cout << "Value of stringREF : " << stringREF << std::endl;

	return (0);
}