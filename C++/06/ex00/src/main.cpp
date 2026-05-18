/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbonneau <sbonneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 23:29:28 by sbonneau          #+#    #+#             */
/*   Updated: 2026/01/29 01:38:48 by sbonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ScalarConverter.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Only One Argument" << std::endl;
        return (1);
    }

    std::string input = av[1];

    if (input.empty())
    {
        std::cout << "Empty argument" << std::endl;
        return (1);
    }

    ScalarConverter::convert(input);

    return (0);
}